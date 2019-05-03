#include "piecesmodel.h"

#include <QTimer>


PiecesModel::PiecesModel(Game const& game) :
    mGame(game)
{
    connect(&mGame, &Game::piecesReset, this, &PiecesModel::onPiecesReset);
    connect(&mGame, &Game::pieceMoved, this, &PiecesModel::onPieceMoved);
    connect(&mGame, &Game::pieceAdded, this, &PiecesModel::onPieceAdded);
    connect(&mGame, &Game::pieceRemoved, this, &PiecesModel::onPieceRemoved);

    onPiecesReset();
}

QHash<int, QByteArray> PiecesModel::roleNames() const
{
    return
    {
        {Color, "color"},
        {Type, "type"},
        {X, "x"},
        {Y, "y"},
    };
}

QVariant PiecesModel::data(const QModelIndex & index, int role) const
{
    QVariant data;

    auto row = static_cast<size_t>(index.row());

    if(row < mPieces.size())
    {
        auto piece = mPieces.at(row);

        switch (role)
        {
        case Color:
            data = QVariant(piece.mColor);
            break;
        case Type:
            data = QVariant(piece.mType);
            break;
        case X:
            data = QVariant(piece.mX);
            break;
        case Y:
            data = QVariant(piece.mY);
            break;
        default:
            assert(false);
        }
    }

    return data;
}

int PiecesModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)

    return static_cast<int>(mPieces.size());
}

void PiecesModel::onPieceMoved(int originX, int originY, int destinationX, int destinationY)
{
    for(size_t i=0; i<mPieces.size(); ++i)
    {
        auto& piece = mPieces[i];

        if(piece.mX == originX && piece.mY == originY)
        {
            piece.mX = destinationX;
            piece.mY = destinationY;
            emit dataChanged(index(static_cast<int>(i)), index(static_cast<int>(i)), {X, Y});
            break;
        }
    }
}

void PiecesModel::onPieceAdded()
{

}

void PiecesModel::onPieceRemoved(int x, int y)
{
    Q_UNUSED(x)
    Q_UNUSED(y)
}

void PiecesModel::onPiecesReset()
{
    beginResetModel();

    mPieces.clear();

    auto board = mGame.getBoard();

    for(size_t i=0; i<board.size(); i++)
    {
        for(size_t j=0; j<board[i].size(); ++j)
        {
            auto const& square = board[i][j];

            switch (square)
            {
            case Piece::EWhitePawn:
                mPieces.emplace_back("white", "pawn", i, j);
                break;
            case Piece::EBlackPawn:
                mPieces.emplace_back("black", "pawn", i, j);
                break;
            default:
                continue;
            }
        }
    }

    endResetModel();
}
