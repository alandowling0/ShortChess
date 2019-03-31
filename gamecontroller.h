#pragma once

#include "piecesmodel.h"
#include "highlightsmodel.h"

#include <QObject>

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(PiecesModel& piecesModel, HighlightsModel& highlightsModel);

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void showDestinations(int x, int y);
    Q_INVOKABLE void clearDestinations();
    Q_INVOKABLE void doMove(int fromX, int fromY, int toX, int toY);


private:
    PiecesModel& mPiecesModel;
    HighlightsModel& mHighlightsModel;
};
