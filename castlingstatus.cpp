#include "castlingstatus.h"
#include <QtGlobal>

bool CastlingStatus::isCastlingAllowed(Color color, Side side) const
{
    auto castlingAllowed = false;

    Q_ASSERT(color == Color::EWhite || color == Color::EBlack);
    Q_ASSERT(side == Side::Kingside || side == Side::Queenside);

    if(color == Color::EWhite)
    {
        if(side == Side::Kingside)
        {
            castlingAllowed = mWhiteKingside;
        }
        else if(side == Side::Queenside)
        {
            castlingAllowed = mWhiteQueenside;
        }
    }
    else if(color == Color::EBlack)
    {
        if(side == Side::Kingside)
        {
            castlingAllowed = mBlackKingside;
        }
        else if(side == Side::Queenside)
        {
            castlingAllowed = mBlackQueenside;
        }
    }

    return castlingAllowed;
}

