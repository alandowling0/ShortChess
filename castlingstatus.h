#ifndef CASTLINGSTATUS_H
#define CASTLINGSTATUS_H

#include "color.h"

#include "color.h"
#include "side.h"

class CastlingStatus
{
    bool isCastlingAllowed(Color color, Side side) const;

private:

    bool mWhiteKingside;
    bool mWhiteQueenside;
    bool mBlackKingside;
    bool mBlackQueenside;
};

#endif // CASTLINGSTATUS_H
