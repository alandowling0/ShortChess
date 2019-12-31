#include "piecesmodel.h"


PiecesModel::PiecesModel(Board const& board) :
    mBoard(board)
{
    connect(&mBoard, &Board::cleared, this, &PiecesModel::onCleared);
    connect(&mBoard, &Board::pieceMoved, this, &PiecesModel::onPieceMoved);
    connect(&mBoard, &Board::pieceAdded, this, &PiecesModel::onPieceAdded);
    connect(&mBoard, &Board::pieceRemoved, this, &PiecesModel::onPieceRemoved);
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

    auto row = index.row();

    if(row < mBoard.numOfPieces())
    {
        auto piece = mBoard.pieceInfo(row);

        switch (role)
        {
        case Image:
            data = QVariant(image(piece.mPiece));
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

    return mBoard.numOfPieces();
}

void PiecesModel::onPieceAdded(int index)
{
    beginInsertRows(QModelIndex(), index, index);
    endInsertRows();
}

void PiecesModel::onPieceRemoved(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    endRemoveRows();
}

void PiecesModel::onPieceMoved(int index)
{
    auto theIndex = QAbstractListModel::index(index);
    emit dataChanged(theIndex, theIndex, {X, Y});
}

void PiecesModel::onCleared()
{
    beginResetModel();
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
