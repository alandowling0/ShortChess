#pragma once

#include "piece.h"
#include "square.h"

#include <QAbstractListModel>
#include <vector>


class PiecesModel : public QAbstractListModel
{
    Q_OBJECT

    struct PieceInfo
    {
        PieceInfo(int x, int y, Piece piece) :
            mX(x),
            mY(y),
            mPiece(piece)
        {
        }

        int mX;
        int mY;
        Piece mPiece;
    };

public:
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    Piece piece(Square const& square) const;

    void setPiece(Square const& square, Piece piece);
    void movePiece(Square const& origin, Square const& destination);
    void clear();

private:
    void addPiece(Square const& square, Piece piece);
    void removePiece(Square const& square);
    QString image(Piece piece) const;

    enum PieceRole
    {
        Image = Qt::UserRole + 1,
        X,
        Y
    };

    std::vector<PieceInfo> mPieces;
};
