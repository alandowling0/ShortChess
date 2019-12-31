#include "model.h"

Model::Model() :
    mGame(mBoard),
    mPiecesModel(std::make_unique<PiecesModel>(mBoard)),
    mSelected{-1, -1}
{
}

void Model::newGame()
{
    mGame.newGame();
    emit gameStateChanged();

    mHighlighted.clear();
    emit highlightedChanged();

    mSelected = {-1, -1};
    emit selectedChanged();
}

void Model::undoMove()
{
    mGame.undoMove();
    emit gameStateChanged();

    mHighlighted.clear();
    emit highlightedChanged();

    mSelected = {-1, -1};
    emit selectedChanged();
}

void Model::redoMove()
{
    mGame.redoMove();
    emit gameStateChanged();

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
        legalMoves = mGame.getLegalMoves(Square(mSelected.first, mSelected.second));
    }
    auto iter = std::find_if(legalMoves.begin(), legalMoves.end(), [x, y](auto move){
        return move.destination().x() == x && move.destination().y() == y;
    });

    if(iter != legalMoves.end())
    {
        mGame.playMove(*iter);
        emit gameStateChanged();

        mSelected = {-1, -1};
        mHighlighted.clear();
    }
    else
    {
        auto sideToMove = mGame.sideToMove();

        if(x < mBoard.rows() && y < mBoard.columns())
        {
            auto piece = mBoard.piece(Square{x, y});

            auto selectable = (PieceUtils::isWhite(piece) && sideToMove == Color::EWhite) ||
                                (PieceUtils::isBlack(piece) && sideToMove == Color::EBlack);

            if(selectable)
            {
                mSelected = {x, y};

                auto moves = mGame.getLegalMoves(Square(x, y));

                mHighlighted.clear();
                for(auto const& m : moves)
                {
                    mHighlighted.insert({m.destination().x(), m.destination().y()});
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

bool Model::undoMoveAvailable() const
{
    return mGame.getMovesPlayed().size() > 0;
}

bool Model::redoMoveAvailable() const
{
    return mGame.getMovesUndone().size() > 0;
}
