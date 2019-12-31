#pragma once

#include <QObject>
#include "piece.h"
#include "square.h"
#include <vector>

class Board : public QObject
{
    Q_OBJECT

    struct PieceInfo
    {
        PieceInfo(int x, int y, Piece piece) :
            mX(x),
            mY(y),
            mPiece(piece)
        {
        }

        int mX;
        int mY;
        Piece mPiece;
    };

public:
    int rows() const;
    int columns() const;
    bool isValidSquare(Square const& square) const;
    Piece piece(Square const& square) const;
    PieceInfo pieceInfo(int index) const;
    int numOfPieces() const;

    void setPiece(Square const& square, Piece piece);
    void movePiece(Square const& origin, Square const& destination);
    void clear();

signals:
    void pieceAdded(int index);
    void pieceRemoved(int index);
    void pieceMoved(int index);
    void cleared();

private:
    void addPiece(Square const& square, Piece piece);
    void removePiece(Square const& square);

    std::vector<PieceInfo> mPieces;
};

