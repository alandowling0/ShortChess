#include "movegeneration.h"
#include <QtGlobal>

namespace
{
    std::vector<Move> getKingMoves(Position const& position, Square const& origin);
    std::vector<Move> getPawnMoves(Position const& position, Square const& origin);
    void appendPawnMoves(Position const& position, Square const& origin, int yDelta, std::vector<Move>& moves);
    void appendPawnCapture(Position const& position, Square const& origin, Square const& destination, std::vector<Move> &moves);
}

std::vector<Move> MoveGeneration::getMoves(const Position &position)
{
    auto moves = std::vector<Move>();

    for(auto i = 0; i < position.size(); ++i)
    {
        for(auto j = 0; j < position.size(); ++j)
        {
            auto square = Square{i, j};

            auto piece = position.piece(square);

            if(PieceUtils::color(piece) == position.sideToMove())
            {
                auto pieceMoves = getMoves(position, square);

                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGeneration::getMoves(Position const& position, Square const& square)
{
    Q_ASSERT(position.isValidSquare(square));

    auto moves = std::vector<Move>();

    auto piece = position.piece(square);

    switch(piece)
    {
    case Piece::EWhitePawn:
    case Piece::EBlackPawn:
        moves = getPawnMoves(position, square);
        break;
    case Piece::EWhiteKing:
    case Piece::EBlackKing:
        moves = getKingMoves(position, square);
        break;
    default:
        Q_ASSERT(false);
    }

    return moves;
}

namespace
{
    std::vector<Move> getKingMoves(Position const& position, Square const& origin)
    {
        std::vector<Move> moves;

        for(auto dX = -1; dX <= 1; ++dX)
        {
            for(auto dY = -1; dY <= 1; ++dY)
            {
                if(dX == 0 && dY == 0)
                {
                    continue;
                }

                auto destination = Square{origin.x() + dX, origin.y() + dY};

                if(position.isValidSquare(destination))
                {
                    auto piece = position.piece(origin);
                    auto destinationPiece = position.piece(destination);

                    auto canMove = destinationPiece == Piece::ENone;
                    auto canCapture = (PieceUtils::isWhite(piece) != PieceUtils::isWhite(destinationPiece));

                    if(canMove || canCapture)
                    {
                        moves.emplace_back(origin, destination, piece, destinationPiece);
                    }
                }
            }
        }

        return moves;
    }

    std::vector<Move> getPawnMoves(Position const& position, Square const& origin)
    {
        std::vector<Move> moves;

        // white pawns will move in one direction and black pawns in the other
        auto piece = position.piece(origin);
        auto yDelta = PieceUtils::isWhite(piece) ? -1 : 1;

        appendPawnMoves(position, origin, yDelta, moves);

        auto squareForwardLeft = Square{origin.x() + yDelta, origin.y() + yDelta};
        if(position.isValidSquare(squareForwardLeft))
        {
            appendPawnCapture(position, origin, squareForwardLeft, moves);
        }

        auto squareForwardRight = Square{origin.x() - yDelta, origin.y() + yDelta};
        if(position.isValidSquare(squareForwardRight))
        {
            appendPawnCapture(position, origin, squareForwardRight, moves);
        }

        return moves;
    }

    void appendPawnMoves(Position const& position, Square const& origin, int yDelta, std::vector<Move>& moves)
    {
        auto destination = Square{origin.x(), origin.y() + yDelta};

        if(position.isValidSquare(destination))
        {
            if(position.piece(destination) == Piece::ENone)
            {
                auto piece = position.piece(origin);

                moves.emplace_back(origin, destination, piece);

                auto onStartSquare = !position.isValidSquare(Square{origin.x(), origin.y() - (yDelta*2)});

                if(onStartSquare)
                {
                    auto squareForwardTwo = Square{origin.x(), origin.y() + (yDelta*2)};

                    auto canMoveForwardTwo =
                        position.isValidSquare(squareForwardTwo) &&
                        position.piece(squareForwardTwo) == Piece::ENone;

                    if(canMoveForwardTwo)
                    {
                        moves.emplace_back(origin, squareForwardTwo, piece);
                    }
                }
            }
        }
    }

    void appendPawnCapture(const Position &position, Square const& origin, Square const& destination, std::vector<Move> &moves)
    {
        auto piece = position.piece(origin);
        auto pieceToCapture = position.piece(destination);
        auto enPassantSquare = position.availableEnPassant();

        if(pieceToCapture != Piece::ENone)
        {
            // check for a normal capture
            auto isOppositeColor = PieceUtils::isWhite(piece) != PieceUtils::isWhite(pieceToCapture);

            if(isOppositeColor)
            {
                moves.emplace_back(origin, destination, piece, pieceToCapture);
            }
        }
        else if(position.isValidSquare(enPassantSquare))
        {
            // check if en passant capture is possible
            auto sameRow = enPassantSquare.y() == origin.y();
            auto adjacentColumn = enPassantSquare.x() == destination.x();

            if(sameRow && adjacentColumn)
            {
                moves.emplace_back(origin, destination, piece, position.piece(enPassantSquare), true);
            }
        }
    }
}
