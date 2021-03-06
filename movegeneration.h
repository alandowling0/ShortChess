#pragma once

#include "move.h"
#include "square.h"
#include "color.h"
#include "position.h"
#include <vector>

namespace MoveGeneration
{
    std::vector<Move> getMoves(Position const& position);
    std::vector<Move> getMoves(Position const& position, Square const& origin);
    std::vector<Move> removeMovesAllowingCheck(Position const& position, std::vector<Move> const& moves);
}
