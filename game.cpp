#include "game.h"

Game::Game(Board& board) :
    mBoard(board)
{
    resetPieces();
}

void Game::playMove(Move const& move)
{
    mMovesUndone.clear();

    doMove(move);
}

void Game::undoMove()
{
    if(mMoves.size() > 0)
    {
        auto move = mMoves.back();
        mMoves.pop_back();

        mBoard.movePiece(move.destination(), move.origin());

        auto captured = move.captured();
        if(captured != Piece::ENone)
        {
            auto capturedPieceX = move.destination().x();
            auto capturedPieceY = move.destination().y();

            if(move.enPassant())
            {
                capturedPieceY = move.origin().y();
            }

            mBoard.setPiece(Square{capturedPieceX, capturedPieceY}, captured);
        }

        mMovesUndone.emplace_back(move);
    }
    else
    {
        Q_ASSERT(false);
    }
}

void Game::redoMove()
{
    if(mMovesUndone.size() > 0)
    {
        doMove(mMovesUndone.back());

        mMovesUndone.pop_back();
    }
    else
    {
        Q_ASSERT(false);
    }
}

void Game::newGame()
{
    mMoves.clear();
    mMovesUndone.clear();

    resetPieces();
}

std::vector<Move> Game::getMovesPlayed() const
{
    return mMoves;
}

std::vector<Move> Game::getMovesUndone() const
{
    return mMovesUndone;
}

std::vector<Move> Game::getLegalMoves(Square const& origin) const
{
    std::vector<Move> moves;

    switch(mBoard.piece(origin))
    {
    case Piece::EWhitePawn:
    case Piece::EBlackPawn:
        moves = getPawnMoves(origin);
        break;
    case Piece::EWhiteKing:
    case Piece::EBlackKing:
        moves = getKingMoves(origin);
        break;
    default:
        Q_ASSERT(false);
    }

    return moves;
}

Color Game::sideToMove() const
{
    return (mMoves.size() % 2 == 0) ? Color::EWhite : Color::EBlack;
}

void Game::doMove(Move const& move)
{
    mMoves.push_back(move);

    // remove the piece being captured if any
    if(move.captured() != Piece::ENone)
    {
        auto capturedSquare = move.destination();
        if(move.enPassant())
        {
            capturedSquare = Square{move.destination().x(), move.origin().y()};
        }

        mBoard.setPiece(capturedSquare, Piece::ENone);
    }

    // move the piece being moved
    mBoard.movePiece(move.origin(), move.destination());
}

void Game::resetPieces()
{
    mBoard.clear();

    mBoard.setPiece(Square{0, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{1, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{2, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{3, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{4, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{5, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{6, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{7, 6}, Piece::EWhitePawn);

    mBoard.setPiece(Square{4, 7}, Piece::EWhiteKing);

    mBoard.setPiece(Square{0, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{1, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{2, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{3, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{4, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{5, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{6, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{7, 1}, Piece::EBlackPawn);

    mBoard.setPiece(Square{4, 0}, Piece::EBlackKing);
}

std::vector<Move> Game::getPawnMoves(Square const& origin) const
{
    std::vector<Move> moves;

    // white pawns will move in one direction and black pawns in the other
    auto piece = mBoard.piece(origin);
    auto yDelta = PieceUtils::isWhite(piece) ? -1 : 1;

    getPawnMovesForward(origin, yDelta, moves);

    auto squareForwardLeft = Square{origin.x() + yDelta, origin.y() + yDelta};
    if(mBoard.isValidSquare(squareForwardLeft))
    {
        getPawnCaptures(origin, squareForwardLeft, moves);
    }

    auto squareForwardRight = Square{origin.x() - yDelta, origin.y() + yDelta};
    if(mBoard.isValidSquare(squareForwardRight))
    {
        getPawnCaptures(origin, squareForwardRight, moves);
    }

    return moves;
}

void Game::getPawnMovesForward(Square const& origin, int yDelta, std::vector<Move>& moves) const
{
    auto destination = Square{origin.x(), origin.y() + yDelta};

    if(mBoard.isValidSquare(destination))
    {
        if(mBoard.piece(destination) == Piece::ENone)
        {
            auto piece = mBoard.piece(origin);

            moves.emplace_back(origin, destination, piece);

            auto onStartSquare = !mBoard.isValidSquare(Square{origin.x(), origin.y() - (yDelta*2)});

            if(onStartSquare)
            {
                auto squareForwardTwo = Square{origin.x(), origin.y() + (yDelta*2)};

                auto canMoveForwardTwo =
                    mBoard.isValidSquare(squareForwardTwo) &&
                    mBoard.piece(squareForwardTwo) == Piece::ENone;

                if(canMoveForwardTwo)
                {
                    moves.emplace_back(origin, squareForwardTwo, piece);
                }
            }
        }
    }
}

void Game::getPawnCaptures(Square const& origin, Square const& destination, std::vector<Move> &moves) const
{
    auto piece = mBoard.piece(origin);
    auto pieceToCapture = mBoard.piece(destination);

    if(pieceToCapture != Piece::ENone)
    {
        // check for a normal capture
        auto isOppositeColor = PieceUtils::isWhite(piece) != PieceUtils::isWhite(pieceToCapture);

        if(isOppositeColor)
        {
            moves.emplace_back(origin, destination, piece, pieceToCapture);
        }
    }
    else if(mMoves.size() > 0)
    {
        // check if en passant capture is possible
        auto previousMove = mMoves.back();

        auto wasPawnMove =
            previousMove.piece() == Piece::EWhitePawn ||
            previousMove.piece() == Piece::EBlackPawn;

        auto wasAdjacent = (previousMove.destination().x() == destination.x()) && (previousMove.destination().y() == origin.y());

        auto movedTwoSquares = std::abs(previousMove.origin().y() - previousMove.destination().y()) == 2;

        if(wasPawnMove && wasAdjacent && movedTwoSquares)
        {
            moves.emplace_back(origin, destination, piece, previousMove.piece(), true);
        }
    }
}

std::vector<Move> Game::getKingMoves(const Square &origin) const
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

            if(mBoard.isValidSquare(destination))
            {
                auto piece = mBoard.piece(origin);
                auto destinationPiece = mBoard.piece(destination);

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

