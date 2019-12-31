#include "board.h"

int Board::rows() const
{
    return 8;
}

int Board::columns() const
{
    return 8;
}

bool Board::isValidSquare(const Square& square) const
{
    auto xOk = square.x() >= 0 && square.x() < columns();
    auto yOk = square.y() >= 0 && square.y() < rows();

    return xOk && yOk;
}

Piece Board::piece(Square const& square) const
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

Board::PieceInfo Board::pieceInfo(int index) const
{
    auto pieceInfo = Board::PieceInfo(0, 0, Piece::ENone);

    auto i = static_cast<size_t>(index);

    if(i < mPieces.size())
    {
        pieceInfo = mPieces[i];
    }
    else
    {
        Q_ASSERT(false);
    }

    return pieceInfo;
}

int Board::numOfPieces() const
{
    return static_cast<int>(mPieces.size());
}

void Board::setPiece(Square const& square, Piece piece)
{
    Q_ASSERT(isValidSquare(square));

    removePiece(square);

    if(piece != Piece::ENone)
    {
        addPiece(square, piece);
    }
}

void Board::movePiece(Square const& origin, Square const& destination)
{
    Q_ASSERT(isValidSquare(origin));
    Q_ASSERT(isValidSquare(destination));

    auto pieceToMove = std::find_if(mPieces.begin(), mPieces.end(), [origin](PieceInfo const& piece){
        return piece.mX == origin.x() && piece.mY == origin.y();
    });

    if(pieceToMove != mPieces.end())
    {
        pieceToMove->mX = destination.x();
        pieceToMove->mY = destination.y();

        emit pieceMoved(static_cast<int>(std::distance(mPieces.begin(), pieceToMove)));
    }
    else
    {
        Q_ASSERT(false);
    }
}

void Board::clear()
{
    mPieces.clear();

    emit cleared();
}

void Board::addPiece(Square const& square, Piece piece)
{
    Q_ASSERT(isValidSquare(square));
    Q_ASSERT(piece != Piece::ENone);

    mPieces.emplace_back(square.x(), square.y(), piece);

    emit pieceAdded(static_cast<int>(mPieces.size() - 1));
}

void Board::removePiece(Square const& square)
{
    Q_ASSERT(isValidSquare(square));

    auto pieceToRemove = std::find_if(mPieces.begin(), mPieces.end(), [square](PieceInfo const& piece){
        return piece.mX == square.x() && piece.mY == square.y();
    });

    if(pieceToRemove != mPieces.end())
    {
        auto index = static_cast<int>(std::distance(mPieces.begin(), pieceToRemove));

        mPieces.erase(pieceToRemove);

        emit pieceRemoved(index);
    }
}
