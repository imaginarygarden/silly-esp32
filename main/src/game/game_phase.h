#ifndef GAME_PHASE_H
#define GAME_PHASE_H

#include <cstdint>

enum class GamePhase : std::uint8_t { IDLE, RUNNING, PAUSED, FINISHED };

#endif