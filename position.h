#pragma once

#include "piece.h"
#include "square.h"
#include "move.h"
#include "board.h"
#include "castlingstatus.h"
#include <vector>

class Position
{
public:
    Position(Board const& board,
             Color sideToMove,
             CastlingStatus const& castlingStatus,
             Square const& availableEnPassant);

    Board board() const;
    Color sideToMove() const;
    CastlingStatus castlingStatus() const;
    Square availableEnPassant() const;

private:
    Board mBoard;
    Color mSideToMove;
    CastlingStatus mCastlingStatus;
    Square mAvailableEnPassant;
};

