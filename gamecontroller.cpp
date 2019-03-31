#include "gamecontroller.h"
#include <QPair>

GameController::GameController(PiecesModel& piecesModel, HighlightsModel& highlightsModel) :
    mPiecesModel(piecesModel), mHighlightsModel(highlightsModel)
{

}

void GameController::newGame()
{
    mPiecesModel.reset();
    mHighlightsModel.clear();
}

void GameController::showDestinations(int x, int y)
{
    mHighlightsModel.setDestinations({
        {rand() % 8, rand() % 8},
        {rand() % 8, rand() % 8},
        {rand() % 8, rand() % 8},
        {rand() % 8, rand() % 8},
        {rand() % 8, rand() % 8},
        {rand() % 8, rand() % 8}
    });
}

void GameController::clearDestinations()
{
    mHighlightsModel.clear();
}

void GameController::doMove(int fromX, int fromY, int toX, int toY)
{
    mPiecesModel.doMove(fromX, fromY, toX, toY);
}

