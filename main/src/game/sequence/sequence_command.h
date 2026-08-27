#ifndef SEQUENCE_COMMAND_H
#define SEQUENCE_COMMAND_H

#include <cstdint>
#include <variant>

struct SequencePress {
    std::uint8_t index{};
};

struct SequenceDisplayFinish {};

using SequenceCommand = std::variant<SequencePress, SequenceDisplayFinish>;

#endif