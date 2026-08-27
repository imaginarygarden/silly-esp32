#ifndef SEQUENCE_STATE_H
#define SEQUENCE_STATE_H

#include <cstdint>
#include <vector>

struct SequenceState final {
    std::uint8_t cols{3};
    std::uint8_t rows{3};
    std::uint8_t level{1};
    std::vector<uint8_t> path{};
    double secondsLeft{60};
};

#endif