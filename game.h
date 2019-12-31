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

    void playMove(Move const& move);
    void undoMove();
    void redoMove();
    void newGame();

    Board<8, 8> getBoard() const;
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getMovesUndone() const;
    std::vector<Move> getLegalMoves(Square const& origin) const;
    Color sideToMove() const;

signals:
    void pieceMoved(int originX, int originY, int destinationX, int destinationY);
    void pieceAdded(int x, int y, Piece piece);
    void pieceRemoved(int x, int y);
    void piecesReset();

private:
    void doMove(Move const& move);
    void resetPieces();

    std::vector<Move> getPawnMoves(Square const& origin) const;
    void getPawnMovesForward(Square const& origin, int yDelta, std::vector<Move>& moves) const;
    void getPawnCaptures(Square const& origin, Square const& destination, std::vector<Move>& moves) const;

    Board<8, 8> mBoard;
    std::vector<Move> mMoves;
    std::vector<Move> mMovesUndone;
};
