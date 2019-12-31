#include "square.h"

Square::Square(int x, int y) :
    mX(x),
    mY(y)
{

}

int Square::x() const
{
    return mX;
}

int Square::y() const
{
    return mY;
}
