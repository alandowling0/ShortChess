#pragma once

#include "color.h"

enum class Piece
{
    ENone,
    EWhitePawn,
    EWhiteKnight,
    EWhiteBishop,
    EWhiteRook,
    EWhiteQueen,
    EWhiteKing,
    EBlackPawn,
    EBlackKnight,
    EBlackBishop,
    EBlackRook,
    EBlackQueen,
    EBlackKing
};

namespace PieceUtils
{
    bool isWhite(Piece piece);

    bool isBlack(Piece piece);

    Color color(Piece piece);
}
