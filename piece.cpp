#include "piece.h"

bool PieceUtils::isWhite(Piece piece)
{
    return piece == Piece::EWhitePawn ||
            piece == Piece::EWhiteKnight ||
            piece == Piece::EWhiteBishop ||
            piece == Piece::EWhiteRook ||
            piece == Piece::EWhiteQueen ||
            piece == Piece::EWhiteKing;
}

bool PieceUtils::isBlack(Piece piece)
{
    return piece == Piece::EBlackPawn ||
            piece == Piece::EBlackKnight ||
            piece == Piece::EBlackBishop ||
            piece == Piece::EBlackRook ||
            piece == Piece::EBlackQueen ||
            piece == Piece::EBlackKing;
}

Color PieceUtils::color(Piece piece)
{
    switch(piece)
    {
    case Piece::EWhitePawn:
    case Piece::EWhiteKnight:
    case Piece::EWhiteBishop:
    case Piece::EWhiteRook:
    case Piece::EWhiteQueen:
    case Piece::EWhiteKing:
        return Color::EWhite;
    case Piece::EBlackPawn:
    case Piece::EBlackKnight:
    case Piece::EBlackBishop:
    case Piece::EBlackRook:
    case Piece::EBlackQueen:
    case Piece::EBlackKing:
        return Color::EBlack;
    default:
        return Color::ENone;
    }
}
