#include "movegeneration.h"
#include <QtGlobal>

namespace
{
    std::vector<Move> getKingMoves(Position const& position, Square const& origin);
    std::vector<Move> getCastlingMoves(Position const& position, Square const& origin);
    std::vector<Move> getQueenMoves(Position const& position, Square const& origin);
    std::vector<Move> getRookMoves(Position const& position, Square const& origin);
    std::vector<Move> getBishopMoves(Position const& position, Square const& origin);
    std::vector<Move> getKnightMoves(Position const& position, Square const& origin);
    std::vector<Move> getPawnMoves(Position const& position, Square const& origin);
    void appendPawnMoves(Position const& position, Square const& origin, int yDelta, std::vector<Move>& moves);
    void appendPawnCapture(Position const& position, Square const& origin, Square const& destination, std::vector<Move> &moves);
    std::vector<Move> getSlidingPieceMoves(Position const& position, Square const& origin, int dX, int dY);
}

std::vector<Move> MoveGeneration::getMoves(const Position &position)
{
    auto moves = std::vector<Move>();

    for(auto i = 0; i < position.board().size(); ++i)
    {
        for(auto j = 0; j < position.board().size(); ++j)
        {
            auto square = Square{i, j};

            auto piece = position.board().piece(square);

            if(PieceUtils::color(piece) == position.sideToMove())
            {
                auto pieceMoves = getMoves(position, square);

                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGeneration::getMoves(Position const& position, Square const& origin)
{
    Q_ASSERT(origin.isValid(position.board()));

    auto moves = std::vector<Move>();

    auto piece = position.board().piece(origin);

    switch(piece)
    {
    case Piece::EWhitePawn:
    case Piece::EBlackPawn:
        moves = getPawnMoves(position, origin);
        break;
    case Piece::EWhiteKnight:
    case Piece::EBlackKnight:
        moves = getKnightMoves(position, origin);
        break;
    case Piece::EWhiteBishop:
    case Piece::EBlackBishop:
        moves = getBishopMoves(position, origin);
        break;
    case Piece::EWhiteRook:
    case Piece::EBlackRook:
        moves = getRookMoves(position, origin);
        break;
    case Piece::EWhiteQueen:
    case Piece::EBlackQueen:
        moves = getQueenMoves(position, origin);
        break;
    case Piece::EWhiteKing:
    case Piece::EBlackKing:
        moves = getKingMoves(position, origin);
        break;
    default:
        Q_ASSERT(false);
    }

    return moves;
}

std::vector<Move> MoveGeneration::removeMovesAllowingCheck(Position const& position, std::vector<Move> const& moves)
{
    auto movesNotAllowingCheck = moves;

    movesNotAllowingCheck.erase(std::remove_if(movesNotAllowingCheck.begin(), movesNotAllowingCheck.end(), [position](auto const& move){
        auto illegal = false;

        auto board = position.board();

        board.setPiece(move.origin(), Piece::ENone);
        board.setPiece(move.destination(), move.piece());

        if(move.enPassant())
        {
            auto capturedEnPassantSquare = Square{move.destination().x(), move.origin().y()};
            board.setPiece(capturedEnPassantSquare, Piece::ENone);
        }

        auto sideToMove = (position.sideToMove() == Color::EWhite) ? Color::EBlack : Color::EWhite;

        auto newPosition = Position{board, sideToMove, position.castlingStatus(), position.availableEnPassant()};

        auto nextMoves = MoveGeneration::getMoves(newPosition);

        for(auto const& m : nextMoves)
        {
            if(m.captured() == Piece::EWhiteKing || m.captured() == Piece::EBlackKing)
            {
                illegal = true;
                break;
            }
        }

        return illegal;

    }), movesNotAllowingCheck.end());

    return movesNotAllowingCheck;
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

                if(destination.isValid(position.board()))
                {
                    auto piece = position.board().piece(origin);
                    auto destinationPiece = position.board().piece(destination);

                    auto canMove = destinationPiece == Piece::ENone;
                    auto canCapture = (PieceUtils::isWhite(piece) != PieceUtils::isWhite(destinationPiece));

                    if(canMove || canCapture)
                    {
                        moves.emplace_back(origin, destination, piece, destinationPiece);
                    }
                }
            }
        }

        auto castlingMoves = getCastlingMoves(position, origin);

        moves.insert(moves.begin(), castlingMoves.begin(), castlingMoves.end());

        return moves;
    }

    std::vector<Move> getCastlingMoves(Position const& /*position*/, Square const& /*origin*/)
    {
        std::vector<Move> moves;

        //auto king = position.piece(origin);

        //if()

        return moves;
    }

    std::vector<Move> getQueenMoves(Position const& position, Square const& origin)
    {
        std::vector<Move> moves;

        auto straightMoves = getRookMoves(position, origin);
        moves.insert(moves.begin(), straightMoves.begin(), straightMoves.end());

        auto diagonalMoves = getBishopMoves(position, origin);
        moves.insert(moves.begin(), diagonalMoves.begin(), diagonalMoves.end());

        return moves;
    }

    std::vector<Move> getRookMoves(Position const& position, Square const& origin)
    {
        std::vector<Move> moves;

        auto movesUp = getSlidingPieceMoves(position, origin, 0, -1);
        moves.insert(moves.end(), movesUp.begin(), movesUp.end());

        auto movesDown = getSlidingPieceMoves(position, origin, 0, 1);
        moves.insert(moves.end(), movesDown.begin(), movesDown.end());

        auto movesLeft = getSlidingPieceMoves(position, origin, -1, 0);
        moves.insert(moves.end(), movesLeft.begin(), movesLeft.end());

        auto movesRight = getSlidingPieceMoves(position, origin, 1, 0);
        moves.insert(moves.end(), movesRight.begin(), movesRight.end());

        return moves;
    }

    std::vector<Move> getBishopMoves(Position const& position, Square const& origin)
    {
        std::vector<Move> moves;

        auto movesUpRight = getSlidingPieceMoves(position, origin, 1, -1);
        moves.insert(moves.end(), movesUpRight.begin(), movesUpRight.end());

        auto movesUpLeft = getSlidingPieceMoves(position, origin, -1, -1);
        moves.insert(moves.end(), movesUpLeft.begin(), movesUpLeft.end());

        auto movesDownRight = getSlidingPieceMoves(position, origin, 1, 1);
        moves.insert(moves.end(), movesDownRight.begin(), movesDownRight.end());

        auto movesDownLeft = getSlidingPieceMoves(position, origin, -1, 1);
        moves.insert(moves.end(), movesDownLeft.begin(), movesDownLeft.end());

        return moves;
    }

    std::vector<Move> getKnightMoves(Position const& position, Square const& origin)
    {
        std::vector<Move> moves;

        for(auto dX = -2; dX <= 2; ++dX)
        {
            for(auto dY = -2; dY <= 2; ++dY)
            {
                if((std::abs(dX) + std::abs(dY)) == 3)
                {
                    auto destination = Square{origin.x() + dX, origin.y() + dY};

                    if(destination.isValid(position.board()))
                    {
                        auto piece = position.board().piece(origin);
                        auto pieceColor = PieceUtils::color(piece);

                        auto destinationPiece = position.board().piece(destination);
                        auto destinationColor = PieceUtils::color(destinationPiece);

                        if(pieceColor != destinationColor)
                        {
                            moves.emplace_back(origin, destination, piece, destinationPiece);
                        }
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
        auto piece = position.board().piece(origin);
        auto yDelta = PieceUtils::isWhite(piece) ? -1 : 1;

        appendPawnMoves(position, origin, yDelta, moves);

        auto squareForwardLeft = Square{origin.x() + yDelta, origin.y() + yDelta};
        if(squareForwardLeft.isValid(position.board()))
        {
            appendPawnCapture(position, origin, squareForwardLeft, moves);
        }

        auto squareForwardRight = Square{origin.x() - yDelta, origin.y() + yDelta};
        if(squareForwardRight.isValid(position.board()))
        {
            appendPawnCapture(position, origin, squareForwardRight, moves);
        }

        return moves;
    }

    void appendPawnMoves(Position const& position, Square const& origin, int yDelta, std::vector<Move>& moves)
    {
        auto destination = Square{origin.x(), origin.y() + yDelta};

        if(destination.isValid(position.board()))
        {
            if(position.board().piece(destination) == Piece::ENone)
            {
                auto piece = position.board().piece(origin);

                moves.emplace_back(origin, destination, piece);

                auto back2 = Square{origin.x(), origin.y() - (yDelta*2)};
                auto onStartSquare = !back2.isValid(position.board());

                if(onStartSquare)
                {
                    auto squareForwardTwo = Square{origin.x(), origin.y() + (yDelta*2)};

                    auto canMoveForwardTwo =
                        squareForwardTwo.isValid(position.board()) &&
                        position.board().piece(squareForwardTwo) == Piece::ENone;

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
        auto piece = position.board().piece(origin);
        auto pieceToCapture = position.board().piece(destination);
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
        else if(enPassantSquare.isValid(position.board()))
        {
            // check if en passant capture is possible
            auto sameRow = enPassantSquare.y() == origin.y();
            auto adjacentColumn = enPassantSquare.x() == destination.x();

            if(sameRow && adjacentColumn)
            {
                moves.emplace_back(origin, destination, piece, position.board().piece(enPassantSquare), true);
            }
        }
    }

    std::vector<Move> getSlidingPieceMoves(Position const& position, Square const& origin, int dX, int dY)
    {
        std::vector<Move> moves;

        auto validDeltas = dX != 0 || dY != 0;

        if(validDeltas)
        {
            auto destination = Square{origin.x() + dX, origin.y() + dY};

            while(destination.isValid(position.board()))
            {
                auto pieceAtDestination = position.board().piece(destination);

                if(PieceUtils::color(pieceAtDestination) != position.sideToMove())
                {
                    moves.emplace_back(origin, destination, position.board().piece(origin), pieceAtDestination);
                }

                if(pieceAtDestination == Piece::ENone)
                {
                    destination = Square{destination.x() + dX, destination.y() + dY};
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            Q_ASSERT(false);
        }

        return moves;
    }
}
