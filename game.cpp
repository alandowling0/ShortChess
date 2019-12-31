#include "game.h"

Game::Game()
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

        auto piece = move.piece();
        mBoard.setPiece(move.origin(), piece);
        mBoard.setPiece(move.destination(), Piece::ENone);
        emit pieceMoved(move.destination().x(), move.destination().y(), move.origin().x(), move.origin().y());

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
            emit pieceAdded(capturedPieceX, capturedPieceY, captured);
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

Board<8, 8> Game::getBoard() const
{
    return mBoard;
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
    if(move.enPassant())
    {
        mBoard.setPiece(Square{move.destination().x(), move.origin().y()}, Piece::ENone);
        emit pieceRemoved(move.destination().x(), move.origin().y());
    }
    else if(move.captured() != Piece::ENone)
    {
        emit pieceRemoved(move.destination().x(), move.destination().y());
    }

    // move the piece being moved
    mBoard.setPiece(move.origin(), Piece::ENone);
    mBoard.setPiece(move.destination(), move.piece());
    emit pieceMoved(move.origin().x(), move.origin().y(), move.destination().x(), move.destination().y());
}

void Game::resetPieces()
{
    mBoard = Board<8, 8>();

    mBoard.setPiece(0, 6, Piece::EWhitePawn);
    mBoard.setPiece(1, 6, Piece::EWhitePawn);
    mBoard.setPiece(2, 6, Piece::EWhitePawn);
    mBoard.setPiece(3, 6, Piece::EWhitePawn);
    mBoard.setPiece(4, 6, Piece::EWhitePawn);
    mBoard.setPiece(5, 6, Piece::EWhitePawn);
    mBoard.setPiece(6, 6, Piece::EWhitePawn);
    mBoard.setPiece(7, 6, Piece::EWhitePawn);

    mBoard.setPiece(0, 1, Piece::EBlackPawn);
    mBoard.setPiece(1, 1, Piece::EBlackPawn);
    mBoard.setPiece(2, 1, Piece::EBlackPawn);
    mBoard.setPiece(3, 1, Piece::EBlackPawn);
    mBoard.setPiece(4, 1, Piece::EBlackPawn);
    mBoard.setPiece(5, 1, Piece::EBlackPawn);
    mBoard.setPiece(6, 1, Piece::EBlackPawn);
    mBoard.setPiece(7, 1, Piece::EBlackPawn);

    emit piecesReset();
}

std::vector<Move> Game::getPawnMoves(Square const& origin) const
{
    std::vector<Move> moves;

    // white pawns will move in one direction and black pawns in the other
    auto piece = mBoard.piece(origin);
    auto yDelta = PieceUtils::isWhite(piece) ? -1 : 1;

    getPawnMovesForward(origin, yDelta, moves);

    auto squareForwardLeft = Square{origin.x() + yDelta, origin.y() + yDelta};
    if(mBoard.isValid(squareForwardLeft))
    {
        getPawnCaptures(origin, squareForwardLeft, moves);
    }

    auto squareForwardRight = Square{origin.x() - yDelta, origin.y() + yDelta};
    if(mBoard.isValid(squareForwardRight))
    {
        getPawnCaptures(origin, squareForwardRight, moves);
    }

    return moves;
}

void Game::getPawnMovesForward(Square const& origin, int yDelta, std::vector<Move>& moves) const
{
    auto destination = Square{origin.x(), origin.y() + yDelta};

    if(mBoard.isValid(destination))
    {
        if(mBoard.piece(destination) == Piece::ENone)
        {
            auto piece = mBoard.piece(origin);

            moves.emplace_back(origin, destination, piece);

            auto onStartSquare = !mBoard.isValid(Square{origin.x(), origin.y() - (yDelta*2)});

            if(onStartSquare)
            {
                auto squareForwardTwo = Square{origin.x(), origin.y() + (yDelta*2)};

                auto canMoveForwardTwo =
                    mBoard.isValid(squareForwardTwo) &&
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

