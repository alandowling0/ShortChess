#pragma once

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
}
