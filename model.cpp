#include "model.h"

Model::Model() :
    mPiecesModel(std::make_unique<PiecesModel>(mGame)),
    mHighlightsModel(std::make_unique<HighlightsModel>()),
    mSelectedX(-1),
    mSelectedY(-1)
{

}

void Model::newGame()
{
    mGame.newGame();

    mHighlightsModel->clear();

    mSelectedX = -1;
    mSelectedY = -1;
    emit selectedSquareChanged();
}

void Model::selectSquare(int x, int y)
{
    auto legalMoves = mGame.getLegalMoves(mSelectedX, mSelectedY);
    auto iter = std::find_if(legalMoves.begin(), legalMoves.end(), [x, y](auto move){
        return move.mDestinationX == x && move.mDestinationY == y;
    });

    if(iter != legalMoves.end())
    {
        mGame.doMove(*iter);
        mSelectedX = -1;
        mSelectedY = -1;
        mHighlightsModel->clear();
    }
    else
    {
        auto sideToMove = mGame.sideToMove();
        auto board = mGame.getBoard();

        auto xUnsigned = static_cast<size_t>(x);
        auto yUnsigned = static_cast<size_t>(y);

        if(xUnsigned < board.size() && yUnsigned < board[xUnsigned].size())
        {
            auto piece = board[xUnsigned][yUnsigned];

            auto selectable = (PieceUtils::isWhite(piece) && sideToMove == Color::EWhite) ||
                                (PieceUtils::isBlack(piece) && sideToMove == Color::EBlack);

            if(selectable)
            {
                mSelectedX = x;
                mSelectedY = y;

                auto moves = mGame.getLegalMoves(x, y);

                QSet<QPair<int, int>> destinations;
                for(auto const& m : moves)
                {
                    destinations.insert({m.mDestinationX, m.mDestinationY});
                }

                mHighlightsModel->setDestinations(destinations);
            }
            else
            {
                mSelectedX = -1;
                mSelectedY = -1;
                mHighlightsModel->clear();
            }
        }
    }

    emit selectedSquareChanged();
}

QVariant Model::piecesModel() const
{
    return QVariant::fromValue(mPiecesModel.get());
}

QVariant Model::highlightsModel() const
{
    return QVariant::fromValue(mHighlightsModel.get());
}

QVariantMap Model::selectedSquare() const
{
    return QVariantMap{{"x", mSelectedX}, {"y", mSelectedY}};
}
