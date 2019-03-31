#include "piecesmodel.h"

#include <QTimer>


PiecesModel::PiecesModel()
{
}

void PiecesModel::reset()
{
    beginResetModel();

    mPieces.clear();

    mPieces.emplace_back("white", "rook", 0, 7);
    mPieces.emplace_back("white", "knight", 1, 7);
    mPieces.emplace_back("white", "bishop", 2, 7);
    mPieces.emplace_back("white", "queen", 3, 7);
    mPieces.emplace_back("white", "king", 4, 7);
    mPieces.emplace_back("white", "bishop", 5, 7);
    mPieces.emplace_back("white", "knight", 6, 7);
    mPieces.emplace_back("white", "rook", 7, 7);

    mPieces.emplace_back("white", "pawn", 0, 6);
    mPieces.emplace_back("white", "pawn", 1, 6);
    mPieces.emplace_back("white", "pawn", 2, 6);
    mPieces.emplace_back("white", "pawn", 3, 6);
    mPieces.emplace_back("white", "pawn", 4, 6);
    mPieces.emplace_back("white", "pawn", 5, 6);
    mPieces.emplace_back("white", "pawn", 6, 6);
    mPieces.emplace_back("white", "pawn", 7, 6);


    mPieces.emplace_back("black", "rook", 0, 0);
    mPieces.emplace_back("black", "knight", 1, 0);
    mPieces.emplace_back("black", "bishop", 2, 0);
    mPieces.emplace_back("black", "queen", 3, 0);
    mPieces.emplace_back("black", "king", 4, 0);
    mPieces.emplace_back("black", "bishop", 5, 0);
    mPieces.emplace_back("black", "knight", 6, 0);
    mPieces.emplace_back("black", "rook", 7, 0);

    mPieces.emplace_back("black", "pawn", 0, 1);
    mPieces.emplace_back("black", "pawn", 1, 1);
    mPieces.emplace_back("black", "pawn", 2, 1);
    mPieces.emplace_back("black", "pawn", 3, 1);
    mPieces.emplace_back("black", "pawn", 4, 1);
    mPieces.emplace_back("black", "pawn", 5, 1);
    mPieces.emplace_back("black", "pawn", 6, 1);
    mPieces.emplace_back("black", "pawn", 7, 1);

    endResetModel();
}

void PiecesModel::doMove(int fromX, int fromY, int toX, int toY)
{
    for(size_t i=0; i<mPieces.size(); ++i)
    {
        auto& piece = mPieces[i];

        if(piece.mX == fromX && piece.mY == fromY)
        {
            piece.mX = toX;
            piece.mY = toY;
            emit dataChanged(index(static_cast<int>(i)), index(static_cast<int>(i)), {X, Y});
            break;
        }
    }
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

