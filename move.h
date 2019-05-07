#pragma once

class Move
{
public:
    Move(int originX, int originY, int destinationX, int destinationY) :
        mOriginX(originX),
        mOriginY(originY),
        mDestinationX(destinationX),
        mDestinationY(destinationY)
    {
    }

    int mOriginX;
    int mOriginY;
    int mDestinationX;
    int mDestinationY;
};
