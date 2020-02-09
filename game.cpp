#include "game.h"
#include "position.h"
#include "movegeneration.h"

Game::Game(PiecesModel& piecesModel) :
    mPiecesModel(piecesModel)
{
    resetPieces();
}

void Game::playMove(Move const& move)
{
    mMovesUndone.clear();

    doMove(move);
}

void Game::takebackMove()
{
    if(mMoves.size() > 0)
    {
        auto move = mMoves.back();
        mMoves.pop_back();

        undoMove(move);
    }
    else
    {
        Q_ASSERT(false);
    }
}

void Game::replayMove()
{
    if(mMovesUndone.size() > 0)
    {
        auto move = mMovesUndone.back();
        mMovesUndone.pop_back();

        doMove(move);
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

std::vector<Move> Game::getMoves(Square const& origin)
{
    auto position = getPosition();

    auto moves = MoveGeneration::getMoves(position, origin);

    return MoveGeneration::removeMovesAllowingCheck(position, moves);
}

std::vector<Move> Game::getMovesPlayed() const
{
    return mMoves;
}

std::vector<Move> Game::getMovesUndone() const
{
    return mMovesUndone;
}

Color Game::getSideToMove() const
{
    return (mMoves.size() % 2 == 0) ? Color::EWhite : Color::EBlack;
}

void Game::doMove(Move const& move)
{
    // remove the piece being captured if any
    if(move.captured() != Piece::ENone)
    {
        auto capturedSquare = move.destination();
        if(move.enPassant())
        {
            capturedSquare = Square{move.destination().x(), move.origin().y()};
        }

        mPiecesModel.setPiece(capturedSquare, Piece::ENone);
    }

    // move the piece being moved
    mPiecesModel.movePiece(move.origin(), move.destination());

    mMoves.push_back(move);
}

void Game::undoMove(Move const& move)
{
    mPiecesModel.movePiece(move.destination(), move.origin());

    auto captured = move.captured();
    if(captured != Piece::ENone)
    {
        auto capturedPieceX = move.destination().x();
        auto capturedPieceY = move.destination().y();

        if(move.enPassant())
        {
            capturedPieceY = move.origin().y();
        }

        mPiecesModel.setPiece(Square{capturedPieceX, capturedPieceY}, captured);
    }

    mMovesUndone.emplace_back(move);
}

void Game::resetPieces()
{
    mPiecesModel.clear();

    mPiecesModel.setPiece(Square{0, 6}, Piece::EWhitePawn);
    mPiecesModel.setPiece(Square{1, 6}, Piece::EWhitePawn);
    mPiecesModel.setPiece(Square{2, 6}, Piece::EWhitePawn);
    mPiecesModel.setPiece(Square{3, 6}, Piece::EWhitePawn);
    mPiecesModel.setPiece(Square{4, 6}, Piece::EWhitePawn);
    mPiecesModel.setPiece(Square{5, 6}, Piece::EWhitePawn);
    mPiecesModel.setPiece(Square{6, 6}, Piece::EWhitePawn);
    mPiecesModel.setPiece(Square{7, 6}, Piece::EWhitePawn);

//    mPiecesModel.setPiece(Square{1, 7}, Piece::EWhiteKnight);
//    mPiecesModel.setPiece(Square{6, 7}, Piece::EWhiteKnight);
//    mPiecesModel.setPiece(Square{2, 7}, Piece::EWhiteBishop);
//    mPiecesModel.setPiece(Square{5, 7}, Piece::EWhiteBishop);
    mPiecesModel.setPiece(Square{0, 7}, Piece::EWhiteRook);
    mPiecesModel.setPiece(Square{7, 7}, Piece::EWhiteRook);
//    mPiecesModel.setPiece(Square{3, 7}, Piece::EWhiteQueen);
    mPiecesModel.setPiece(Square{4, 7}, Piece::EWhiteKing);

    mPiecesModel.setPiece(Square{0, 1}, Piece::EBlackPawn);
    mPiecesModel.setPiece(Square{1, 1}, Piece::EBlackPawn);
    mPiecesModel.setPiece(Square{2, 1}, Piece::EBlackPawn);
    mPiecesModel.setPiece(Square{3, 1}, Piece::EBlackPawn);
    mPiecesModel.setPiece(Square{4, 1}, Piece::EBlackPawn);
    mPiecesModel.setPiece(Square{5, 1}, Piece::EBlackPawn);
    mPiecesModel.setPiece(Square{6, 1}, Piece::EBlackPawn);
    mPiecesModel.setPiece(Square{7, 1}, Piece::EBlackPawn);

    mPiecesModel.setPiece(Square{1, 0}, Piece::EBlackKnight);
    mPiecesModel.setPiece(Square{6, 0}, Piece::EBlackKnight);
    mPiecesModel.setPiece(Square{2, 0}, Piece::EBlackBishop);
    mPiecesModel.setPiece(Square{5, 0}, Piece::EBlackBishop);
    mPiecesModel.setPiece(Square{0, 0}, Piece::EBlackRook);
    mPiecesModel.setPiece(Square{7, 0}, Piece::EBlackRook);
    mPiecesModel.setPiece(Square{3, 0}, Piece::EBlackQueen);
    mPiecesModel.setPiece(Square{4, 0}, Piece::EBlackKing);
}

Position Game::getPosition() const
{
    return {getBoard(), getSideToMove(), getCastlingStatus(), getEnPassantAvailable()};
}

Board Game::getBoard() const
{
    auto board = Board{mBoardSize};

    for(auto i = 0; i < board.size(); ++i)
    {
        for(auto j = 0; j < board.size(); ++j)
        {
            auto square = Square{i, j};
            auto piece = mPiecesModel.piece(square);

            board.setPiece(square, piece);
        }
    }

    return board;
}

CastlingStatus Game::getCastlingStatus() const
{
    auto castlingStatus = CastlingStatus{};

    //look through move history to decide castling rights

    return castlingStatus;
}

Square Game::getEnPassantAvailable() const
{
    auto square = Square{-1, -1};

    // label a pawn as available en passant if the previous move was a pawn moving 2 squares
    if(mMoves.size() > 0)
    {
        auto previousMove = mMoves.back();

        auto wasPawnMove =
            previousMove.piece() == Piece::EWhitePawn ||
            previousMove.piece() == Piece::EBlackPawn;

        auto movedTwoSquares = std::abs(previousMove.origin().y() - previousMove.destination().y()) == 2;

        if(wasPawnMove && movedTwoSquares)
        {
            square = previousMove.destination();
        }
    }

    return square;
}
