#include "piecesmodel.h"


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
        {Image, "image"},
        {X, "x"},
        {Y, "y"}
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
        case Image:
            data = QVariant(piece.mImage);
            break;
        case X:
            data = QVariant(piece.mX);
            break;
        case Y:
            data = QVariant(piece.mY);
            break;
        default:
            Q_ASSERT(false);
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
            auto theIndex = index(static_cast<int>(i));
            emit dataChanged(theIndex, theIndex, {X, Y});
            break;
        }
    }
}

void PiecesModel::onPieceAdded(int x, int y, Piece piece)
{
    auto size = static_cast<int>(mPieces.size());
    beginInsertRows(QModelIndex(), size, size);
    mPieces.emplace_back(image(piece), x, y);
    endInsertRows();
}

void PiecesModel::onPieceRemoved(int x, int y)
{
    for(size_t i=0; i<mPieces.size(); ++i)
    {
        auto& piece = mPieces[i];

        if(piece.mX == x && piece.mY == y)
        {
            auto pos = static_cast<int>(i);
            beginRemoveRows(QModelIndex(), pos, pos);
            mPieces.erase(mPieces.begin() + pos, mPieces.begin() + pos + 1);
            endRemoveRows();
        }
    }
}

void PiecesModel::onPiecesReset()
{
    beginResetModel();

    mPieces.clear();

    auto board = mGame.getBoard();

    for(auto i=0; i<board.size(); i++)
    {
        for(auto j=0; j<board.size(); ++j)
        {
            auto const& piece = board.piece(i, j);

            if(piece != Piece::ENone)
            {
                mPieces.emplace_back(image(piece), i, j);
            }
        }
    }

    endResetModel();
}

QString PiecesModel::image(Piece piece) const
{
    switch(piece)
    {
    case Piece::EWhitePawn:
        return "WhitePawn";
    case Piece::EBlackPawn:
        return "BlackPawn";
    default:
        return QString();
    }
}
