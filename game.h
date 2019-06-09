#pragma once

#include "piece.h"
#include "color.h"
#include "move.h"
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

    std::vector<std::vector<Piece>> getBoard() const;
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getLegalMoves(int originX, int originY) const;
    Color sideToMove() const;

signals:
    void pieceMoved(int originX, int originY, int destinationX, int destinationY);
    void pieceAdded();
    void pieceRemoved(int x, int y);
    void piecesReset();

private:
    void resetPieces();

    std::vector<std::vector<Piece>> mBoard;
    std::vector<Move> mMoves;
};
