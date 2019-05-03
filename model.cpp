#include "model.h"

Model::Model() :
    mPiecesModel(std::make_unique<PiecesModel>(mGame)),
    mHighlightsModel(std::make_unique<HighlightsModel>())
{

}

void Model::newGame()
{
    mGame.newGame();
}

void Model::doMove(int fromX, int fromY, int toX, int toY)
{
    mGame.playMove(Move(fromX, fromY, toX, toY));
}

void Model::showDestinations(int x, int y)
{
    QSet<QPair<int, int>> destinations;

    for(auto const& m : mGame.getLegalMoves(x, y))
    {
        destinations.insert({m.mDestinationX, m.mDestinationY});
    }

    mHighlightsModel->setDestinations(destinations);
}

void Model::clearDestinations()
{
    mHighlightsModel->clear();
}

QVariant Model::piecesModel() const
{
    return QVariant::fromValue(mPiecesModel.get());
}

QVariant Model::highlightsModel() const
{
    return QVariant::fromValue(mHighlightsModel.get());
}

