#include "model.h"

Model::Model() :
    mPiecesModel(std::make_unique<PiecesModel>(mGame)),
    mSelected{-1, -1}
{
    connect(&mGame, &Game::pieceMoved, this, &Model::newGameAvailableChanged);
    connect(&mGame, &Game::piecesReset, this, &Model::newGameAvailableChanged);
}

void Model::newGame()
{
    mGame.newGame();

    mHighlighted.clear();
    emit highlightedChanged();

    mSelected = {-1, -1};
    emit selectedChanged();
}

void Model::selectSquare(int x, int y)
{
    auto squareSelected = mSelected.first >= 0 && mSelected.second >= 0;

    std::vector<Move> legalMoves;
    if(squareSelected)
    {
        legalMoves = mGame.getLegalMoves(mSelected.first, mSelected.second);
    }
    auto iter = std::find_if(legalMoves.begin(), legalMoves.end(), [x, y](auto move){
        return move.mDestinationX == x && move.mDestinationY == y;
    });

    if(iter != legalMoves.end())
    {
        mGame.doMove(*iter);
        mSelected = {-1, -1};
        mHighlighted.clear();
    }
    else
    {
        auto sideToMove = mGame.sideToMove();
        auto board = mGame.getBoard();

        if(x < board.size() && y < board.size())
        {
            auto piece = board.piece(x, y);

            auto selectable = (PieceUtils::isWhite(piece) && sideToMove == Color::EWhite) ||
                                (PieceUtils::isBlack(piece) && sideToMove == Color::EBlack);

            if(selectable)
            {
                mSelected = {x, y};

                auto moves = mGame.getLegalMoves(x, y);

                mHighlighted.clear();
                for(auto const& m : moves)
                {
                    mHighlighted.insert({m.mDestinationX, m.mDestinationY});
                }
            }
            else
            {
                mSelected = {-1, -1};
                mHighlighted.clear();
            }
        }
    }

    emit selectedChanged();
    emit highlightedChanged();
}

QVariant Model::piecesModel() const
{
    return QVariant::fromValue(mPiecesModel.get());
}

QVariantMap Model::selected() const
{
    return QVariantMap{{"x", mSelected.first}, {"y", mSelected.second}};
}

QVariantList Model::highlighted() const
{
    QVariantList highlighted;

    for(auto const& h : mHighlighted)
    {
        highlighted.push_back(QVariantMap{{"x", h.first}, {"y", h.second}});
    }

    return highlighted;
}

bool Model::newGameAvailable() const
{
    return mGame.getMovesPlayed().size() > 0;
}
