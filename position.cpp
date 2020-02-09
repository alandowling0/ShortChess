#include "position.h"


Position::Position(Board const& board,
                   Color sideToMove,
                   CastlingStatus const& castlingStatus,
                   Square const& availableEnPassant) :
    mBoard(board),
    mSideToMove(sideToMove),
    mCastlingStatus(castlingStatus),
    mAvailableEnPassant(availableEnPassant)
{
}


Board Position::board() const
{
    return mBoard;
}

Color Position::sideToMove() const
{
    return mSideToMove;
}

CastlingStatus Position::castlingStatus() const
{
    return mCastlingStatus;
}

Square Position::availableEnPassant() const
{
    return mAvailableEnPassant;
}



