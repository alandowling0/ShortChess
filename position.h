#pragma once

#include "piece.h"
#include "square.h"
#include <vector>

class Position
{
public:
    Position(int size);

    int size() const;
    bool isValidSquare(Square const& square) const;
    void clear();

    Piece piece(Square const& square) const;
    void setPiece(Piece piece, Square const& square);

    Color sideToMove() const;
    void setSideToMove(Color color);

    Square availableEnPassant() const;
    void setAvailableEnPassant(Square const& availableEnPassant);

    bool whiteKingMoved() const;
    void setWhiteKingMoved(bool whiteKingMoved);

    bool whiteKingsideRookMoved() const;
    void setWhiteKingsideRookMoved(bool whiteKingsideRookMoved);

    bool whiteQueensideRookMoved() const;
    void setWhiteQueensideRookMoved(bool whiteQueensideRookMoved);

    bool blackKingMoved() const;
    void setBlackKingMoved(bool blackKingMoved);

    bool blackKingsideRookMoved() const;
    void setBlackKingsideRookMoved(bool blackKingsideRookMoved);

    bool blackQueensideRookMoved() const;
    void setBlackQueensideRookMoved(bool blackQueensideRookMoved);

private:
    std::vector<std::vector<Piece>> mPieces;

    Color mSideToMove;

    Square mAvailableEnPassant;

    bool mWhiteKingMoved;
    bool mWhiteKingsideRookMoved;
    bool mWhiteQueensideRookMoved;

    bool mBlackKingMoved;
    bool mBlackKingsideRookMoved;
    bool mBlackQueensideRookMoved;
};

