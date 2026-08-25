#ifndef SEQUENCE_STATE_H
#define SEQUENCE_STATE_H

#include <cstdint>
#include <vector>
#include <chrono>

struct SequenceState {
    std::uint8_t cols{3};
    std::uint8_t rows{3};
    std::int64_t secondsLeft{};
    std::size_t minutesLimit{1};
    std::size_t level{1};
    std::size_t historyIndex{};
    std::vector<uint8_t> history{};
    std::chrono::time_point<std::chrono::steady_clock> gameStarted{};
};

#endif