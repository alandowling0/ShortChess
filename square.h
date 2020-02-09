#pragma once

#include "board.h"
#include <QHash>

class Square
{
public:
    Square(int x, int y);

    int x() const;
    int y() const;

    bool isValid(Board const& board) const;

private:
    int mX;
    int mY;
};

inline bool operator==(const Square &s1, const Square &s2)
{
    return (s1.x() == s2.x()) && (s1.y() == s2.y());
}

// to enable use in QSet
inline uint qHash(const Square &key, uint seed)
{
    return qHash(key.x(), seed) ^ static_cast<uint>(key.y());
}

