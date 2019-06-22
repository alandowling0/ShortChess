#pragma once

#include "piece.h"

class Move
{
public:
    Move(int originX, int originY, int destinationX, int destinationY) :
        mOriginX(originX),
        mOriginY(originY),
        mDestinationX(destinationX),
        mDestinationY(destinationY),
        mCaptured(Piece::ENone)
    {
    }

    Move(int originX, int originY, int destinationX, int destinationY, Piece captured) :
        mOriginX(originX),
        mOriginY(originY),
        mDestinationX(destinationX),
        mDestinationY(destinationY),
        mCaptured(captured)
    {
    }

    int mOriginX;
    int mOriginY;
    int mDestinationX;
    int mDestinationY;
    Piece mCaptured;
};
