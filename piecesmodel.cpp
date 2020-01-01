#include "piecesmodel.h"

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
        auto piece = mPieces[row];

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

    return static_cast<int>(mPieces.size());
}

Piece PiecesModel::piece(Square const& square) const
{
    Piece pieceType = Piece::ENone;

    for(auto const& piece : mPieces)
    {
        if(piece.mX == square.x() && piece.mY == square.y())
        {
            pieceType = piece.mPiece;
            break;
        }
    }

    return pieceType;
}

void PiecesModel::setPiece(Square const& square, Piece piece)
{
    removePiece(square);

    if(piece != Piece::ENone)
    {
        addPiece(square, piece);
    }
}

void PiecesModel::movePiece(const Square &origin, const Square &destination)
{
    auto pieceToMove = std::find_if(mPieces.begin(), mPieces.end(), [origin](PieceInfo const& piece){
        return piece.mX == origin.x() && piece.mY == origin.y();
    });

    if(pieceToMove != mPieces.end())
    {
        pieceToMove->mX = destination.x();
        pieceToMove->mY = destination.y();

        auto distance = static_cast<int>(std::distance(mPieces.begin(), pieceToMove));
        auto index = QAbstractListModel::index(distance);
        emit dataChanged(index, index, {X, Y});
    }
    else
    {
        Q_ASSERT(false);
    }
}

void PiecesModel::clear()
{
    beginResetModel();

    mPieces.clear();

    endResetModel();
}

void PiecesModel::addPiece(Square const& square, Piece piece)
{
    Q_ASSERT(piece != Piece::ENone);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    mPieces.emplace_back(square.x(), square.y(), piece);

    endInsertRows();
}

void PiecesModel::removePiece(Square const& square)
{
    auto pieceToRemove = std::find_if(mPieces.begin(), mPieces.end(), [square](PieceInfo const& piece){
        return piece.mX == square.x() && piece.mY == square.y();
    });

    if(pieceToRemove != mPieces.end())
    {
        auto index = static_cast<int>(std::distance(mPieces.begin(), pieceToRemove));

        beginRemoveRows(QModelIndex(), index, index);

        mPieces.erase(pieceToRemove);

        endRemoveRows();
    }
}

QString PiecesModel::image(Piece piece) const
{
    switch(piece)
    {
    case Piece::EWhitePawn:
        return "WhitePawn";
    case Piece::EWhiteBishop:
        return "WhiteBishop";
    case Piece::EWhiteRook:
        return "WhiteRook";
    case Piece::EWhiteKing:
        return "WhiteKing";
    case Piece::EBlackPawn:
        return "BlackPawn";
    case Piece::EBlackBishop:
        return "BlackBishop";
    case Piece::EBlackRook:
        return "BlackRook";
    case Piece::EBlackKing:
        return "BlackKing";

    default:
        return QString();
    }
}
