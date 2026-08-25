#ifndef SEQUENCE_STATE_H
#define SEQUENCE_STATE_H

#include <cstdint>
#include <vector>
#include <chrono>

struct SequenceState {
    std::uint8_t cols{3};
    std::uint8_t rows{3};
    std::uint8_t level{1};
    std::uint8_t pathIndex{};
    std::uint8_t playerIndex{};
    std::vector<uint8_t> path{};
    std::chrono::time_point<std::chrono::steady_clock> lastMeasured{};
    double secondsLeft{60};
    bool started{};
    bool lost{};
    bool paused{};
};

#endif