#include "game/sequence/sequence_game.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <limits>

#include "game/game_phase.h"
#include "game/game_result.h"
#include "game/sequence/sequence_command.h"
#include "game/sequence/sequence_phase.h"

namespace {

using namespace std::chrono_literals;

void start_active(SequenceGame& game) {
    game.start();
    game.input(SequenceDisplayFinish{});
}

void require_same_state(const SequenceState& actual,
                        const SequenceState& expected) {
    REQUIRE(actual.cols == expected.cols);
    REQUIRE(actual.rows == expected.rows);
    REQUIRE(actual.level == expected.level);
    REQUIRE(actual.path == expected.path);
    REQUIRE(actual.secondsLeft == Catch::Approx(expected.secondsLeft));
}

}  // namespace

TEST_CASE("A new Sequence game has valid initial state",
          "[sequence][lifecycle]") {
    const SequenceGame game;
    const auto state = game.state();

    REQUIRE(game.phase() == GamePhase::IDLE);
    REQUIRE(game.sequence_phase() == SequencePhase::ACTIVE);
    REQUIRE_FALSE(game.result().has_value());
    REQUIRE(state.cols == 3);
    REQUIRE(state.rows == 3);
    REQUIRE(state.level == 1);
    REQUIRE(state.path.empty());
    REQUIRE(state.secondsLeft == Catch::Approx(60.0));
}

TEST_CASE("Game-specific commands are ignored before Sequence starts",
          "[sequence][commands][lifecycle]") {
    SequenceGame game;
    const auto initial_state = game.state();

    game.input(SequencePress{0});
    game.input(SequenceDisplayFinish{});

    REQUIRE(game.phase() == GamePhase::IDLE);
    REQUIRE(game.sequence_phase() == SequencePhase::ACTIVE);
    REQUIRE_FALSE(game.result().has_value());
    require_same_state(game.state(), initial_state);
}

TEST_CASE("Starting Sequence displays one valid step",
          "[sequence][lifecycle][random]") {
    SequenceGame game;

    game.start();
    const auto state = game.state();
    const auto button_count = state.cols * state.rows;

    REQUIRE(game.phase() == GamePhase::PAUSED);
    REQUIRE(game.sequence_phase() == SequencePhase::DISPLAY);
    REQUIRE_FALSE(game.result().has_value());
    REQUIRE(state.path.size() == 1);
    REQUIRE(state.path.front() < button_count);
}

TEST_CASE("Starting Sequence is idempotent", "[sequence][lifecycle]") {
    SequenceGame game;
    game.start();

    const auto started_state = game.state();
    game.start();

    REQUIRE(game.phase() == GamePhase::PAUSED);
    REQUIRE(game.sequence_phase() == SequencePhase::DISPLAY);
    require_same_state(game.state(), started_state);
}

TEST_CASE("Sequence time advances only while input is active",
          "[sequence][timing][lifecycle]") {
    SequenceGame game;
    game.start();
    const auto initial_time = game.state().secondsLeft;

    SECTION("time is frozen while the pattern is displayed") {
        game.update(1500ms);

        REQUIRE(game.phase() == GamePhase::PAUSED);
        REQUIRE(game.state().secondsLeft == Catch::Approx(initial_time));
    }

    SECTION("finishing the display enables input and the timer") {
        game.input(SequenceDisplayFinish{});
        game.update(1500ms);

        REQUIRE(game.phase() == GamePhase::RUNNING);
        REQUIRE(game.sequence_phase() == SequencePhase::ACTIVE);
        REQUIRE(game.state().secondsLeft == Catch::Approx(initial_time - 1.5));
    }
}

TEST_CASE("Sequence ignores button input while displaying the pattern",
          "[sequence][commands][lifecycle]") {
    SequenceGame game;
    game.start();
    const auto displaying_state = game.state();

    game.input(SequencePress{displaying_state.path.front()});

    REQUIRE(game.phase() == GamePhase::PAUSED);
    REQUIRE(game.sequence_phase() == SequencePhase::DISPLAY);
    require_same_state(game.state(), displaying_state);
}

TEST_CASE("Completing a Sequence pattern advances the level",
          "[sequence][commands][progression]") {
    SequenceGame game;
    start_active(game);

    const auto expected = game.state().path.front();
    game.input(SequencePress{expected});
    const auto state = game.state();

    REQUIRE(state.level == 2);
    REQUIRE(state.path.size() == 2);
    REQUIRE(game.phase() == GamePhase::PAUSED);
    REQUIRE(game.sequence_phase() == SequencePhase::DISPLAY);
    REQUIRE_FALSE(game.result().has_value());
}

TEST_CASE("Sequence waits for the complete pattern before advancing",
          "[sequence][commands][progression]") {
    SequenceGame game;
    start_active(game);

    game.input(SequencePress{game.state().path.front()});
    game.input(SequenceDisplayFinish{});

    const auto level_two_state = game.state();
    REQUIRE(level_two_state.path.size() == 2);

    game.input(SequencePress{level_two_state.path.front()});

    REQUIRE(game.phase() == GamePhase::RUNNING);
    REQUIRE(game.sequence_phase() == SequencePhase::ACTIVE);
    REQUIRE(game.state().level == level_two_state.level);
    REQUIRE(game.state().path == level_two_state.path);
}

TEST_CASE("Wrong Sequence input finishes with a loss",
          "[sequence][commands][result]") {
    SequenceGame game;
    start_active(game);

    const auto state = game.state();
    const auto button_count = state.cols * state.rows;
    const auto wrong =
        static_cast<std::uint8_t>((state.path.front() + 1) % button_count);

    game.input(SequencePress{wrong});

    REQUIRE(game.phase() == GamePhase::FINISHED);
    REQUIRE(game.result() == GameResult::LOSE);
}

TEST_CASE("Out-of-range Sequence input is handled safely",
          "[sequence][commands][boundary]") {
    SequenceGame game;
    start_active(game);

    game.input(SequencePress{std::numeric_limits<std::uint8_t>::max()});

    REQUIRE(game.phase() == GamePhase::FINISHED);
    REQUIRE(game.result() == GameResult::LOSE);
}

TEST_CASE("Sequence timeout finishes with a loss",
          "[sequence][timing][result][boundary]") {
    SequenceGame game;
    start_active(game);

    game.update(60s);

    REQUIRE(game.phase() == GamePhase::FINISHED);
    REQUIRE(game.result() == GameResult::LOSE);
    REQUIRE(game.state().secondsLeft == Catch::Approx(0.0));
}

TEST_CASE("Sequence remains active immediately before timeout",
          "[sequence][timing][boundary]") {
    SequenceGame game;
    start_active(game);

    game.update(59999ms);

    REQUIRE(game.phase() == GamePhase::RUNNING);
    REQUIRE_FALSE(game.result().has_value());
    REQUIRE(game.state().secondsLeft == Catch::Approx(0.001));
}

TEST_CASE("A finished Sequence game is immutable",
          "[sequence][lifecycle][commands]") {
    SequenceGame game;
    start_active(game);
    game.update(60s);

    const auto finished_state = game.state();
    const auto finished_result = game.result();

    game.start();
    game.update(10s);
    game.input(SequenceDisplayFinish{});
    game.input(SequencePress{finished_state.path.front()});

    REQUIRE(game.phase() == GamePhase::FINISHED);
    REQUIRE(game.result() == finished_result);
    require_same_state(game.state(), finished_state);
}

TEST_CASE("Sequence generation is repeatable for the same seed",
          "[sequence][random]") {
    constexpr unsigned int seed = 42;

    std::srand(seed);
    SequenceGame first;
    first.start();
    const auto first_path = first.state().path;

    std::srand(seed);
    SequenceGame second;
    second.start();

    REQUIRE(second.state().path == first_path);
}

TEST_CASE("Sequence does not generate consecutive duplicate steps",
          "[sequence][random][progression]") {
    std::srand(7);
    SequenceGame game;
    game.start();

    constexpr std::size_t rounds = 20;

    for (std::size_t round = 0; round < rounds; ++round) {
        const auto pattern = game.state().path;

        for (std::size_t index = 1; index < pattern.size(); ++index) {
            REQUIRE(pattern[index] != pattern[index - 1]);
        }

        game.input(SequenceDisplayFinish{});
        for (const auto button : pattern) game.input(SequencePress{button});
    }

    REQUIRE(game.state().path.size() == rounds + 1);
    REQUIRE(game.phase() == GamePhase::PAUSED);
    REQUIRE_FALSE(game.result().has_value());
}
