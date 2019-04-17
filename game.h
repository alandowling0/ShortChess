#pragma once

#include <QObject>
#include <vector>

enum class Color
{
    EWhite,
    EBlack
};

enum class Piece
{
    ENone,
    EWhitePawn,
    EWhiteKnight,
    EWhiteBishop,
    EWhiteRook,
    EWhiteQueen,
    EWhiteKing,
    EBlackPawn,
    EBlackKnight,
    EBlackBishop,
    EBlackRook,
    EBlackQueen,
    EBlackKing
};

struct Move
{
    Move(size_t originX, size_t originY, size_t destinationX, size_t destinationY) :
        mOriginX(originX),
        mOriginY(originY),
        mDestinationX(destinationX),
        mDestinationY(destinationY)
    {
    }

    size_t mOriginX;
    size_t mOriginY;
    size_t mDestinationX;
    size_t mDestinationY;
};

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    void doThing();

    void newGame();
    void playMove(Move const& aMove);
    void undoMove();
    void redoMove();

    std::vector<std::vector<Piece>> getBoard() const;
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getLegalMoves(size_t x, size_t y) const;

private:
    Color sideToMove() const;

    std::vector<std::vector<Piece>> mBoard;
    std::vector<Move> mMoves;

signals:
    void alan();
    void pieceMoved(int originX, int originY, int destinationX, int destinationY);
    void pieceAdded();
    void pieceRemoved(int x, int y);
};


//class PawnGame : public Game
//{
//public:
//    PawnGame();


//};
