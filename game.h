#pragma once

#include "piece.h"
#include "color.h"
#include "move.h"
#include "board.h"
#include <QObject>
#include <vector>


class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    void doMove(Move const& aMove);
    void undoMove();
    void redoMove();
    void newGame();

    Board getBoard() const;
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getLegalMoves(int x, int y) const;
    Color sideToMove() const;

signals:
    void pieceMoved(int originX, int originY, int destinationX, int destinationY);
    void pieceAdded();
    void pieceRemoved(int x, int y);
    void piecesReset();

private:
    void resetPieces();

    Board mBoard;
    std::vector<Move> mMoves;
    int mEnPassantX;
};
