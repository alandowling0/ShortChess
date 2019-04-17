#include "gamecontroller.h"
#include <QPair>

GameController::GameController(Game& game, HighlightsModel& highlightsModel) :
    mGame(game), mHighlightsModel(highlightsModel)
{
}

void GameController::newGame()
{
    mGame.newGame();
    mHighlightsModel.clear();
}

void GameController::showDestinations(int x, int y)
{
    QSet<QPair<int, int>> destinations;

    for(auto const& m : mGame.getLegalMoves(x, y))
    {
        destinations.insert({m.mDestinationX, m.mDestinationY});
    }

    mHighlightsModel.setDestinations(destinations);
}

void GameController::clearDestinations()
{
    mHighlightsModel.clear();
}

void GameController::doMove(int fromX, int fromY, int toX, int toY)
{
    mGame.playMove(Move(fromX, fromY, toX, toY));
}

