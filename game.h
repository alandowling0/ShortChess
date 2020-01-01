#pragma once

#include "piece.h"
#include "color.h"
#include "move.h"
#include "position.h"
#include "piecesmodel.h"
#include <QObject>
#include <vector>


class Game : public QObject
{
    Q_OBJECT

public:
    Game(PiecesModel& piecesModel);

    void playMove(Move const& move);
    void takebackMove();
    void replayMove();
    void newGame();

    std::vector<Move> getMoves(Square const& origin);
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getMovesUndone() const;
    Color sideToMove() const;

private:
    Position getPosition() const;
    void doMove(Move const& move);
    void undoMove(Move const& move);
    void resetPieces();

    const int mBoardSize = 8;
    PiecesModel& mPiecesModel;
    std::vector<Move> mMoves;
    std::vector<Move> mMovesUndone;
};
