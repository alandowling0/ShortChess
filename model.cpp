#include "model.h"

Model::Model() :
    mPiecesModel(std::make_unique<PiecesModel>()),
    mGame(*mPiecesModel),
    mSelected{-1, -1}
{
}

void Model::clickSquare(int x, int y)
{
    auto squareClicked = Square{x, y};

    // check if the square being clicked is a valid destination for the currently selected piece
    // if it is then play that move, otherwise update the currently selected piece and highlighted squares
    std::vector<Move> legalMoves;
    if(mPiecesModel->piece(mSelected) != Piece::ENone)
    {
        legalMoves = mGame.getMoves(mSelected);
    }
    auto iter = std::find_if(legalMoves.begin(), legalMoves.end(), [squareClicked](auto move){
        return move.destination() == squareClicked;
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
        auto sideToMove = mGame.getSideToMove();

        auto piece = mPiecesModel->piece(squareClicked);

        auto selectable = (PieceUtils::isWhite(piece) && sideToMove == Color::EWhite) ||
                            (PieceUtils::isBlack(piece) && sideToMove == Color::EBlack);

        if(selectable)
        {
            mSelected = squareClicked;

            auto moves = mGame.getMoves(mSelected);

            mHighlighted.clear();
            for(auto const& m : moves)
            {
                mHighlighted.insert(m.destination());
            }
        }
        else
        {
            mSelected = {-1, -1};
            mHighlighted.clear();
        }
    }

    emit selectedChanged();
    emit highlightedChanged();
}

void Model::takebackMove()
{
    mGame.takebackMove();
    emit gameStateChanged();

    mHighlighted.clear();
    emit highlightedChanged();

    mSelected = {-1, -1};
    emit selectedChanged();
}

void Model::replayMove()
{
    mGame.replayMove();
    emit gameStateChanged();

    mHighlighted.clear();
    emit highlightedChanged();

    mSelected = {-1, -1};
    emit selectedChanged();
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

QVariant Model::piecesModel() const
{
    return QVariant::fromValue(mPiecesModel.get());
}

QVariantMap Model::selected() const
{
    return QVariantMap{{"x", mSelected.x()}, {"y", mSelected.y()}};
}

QVariantList Model::highlighted() const
{
    QVariantList highlighted;

    for(auto const& h : mHighlighted)
    {
        highlighted.push_back(QVariantMap{{"x", h.x()}, {"y", h.y()}});
    }

    return highlighted;
}

bool Model::newGameAvailable() const
{
    return mGame.getMovesPlayed().size() > 0;
}

bool Model::takebackMoveAvailable() const
{
    return mGame.getMovesPlayed().size() > 0;
}

bool Model::replayMoveAvailable() const
{
    return mGame.getMovesUndone().size() > 0;
}
