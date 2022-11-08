#pragma once

#include <iostream>

class Vector2
{
public:
    Vector2();
    Vector2(int Tx, int Ty);

    int Size();

    int X, Y;
};

inline Vector2::Vector2()
{
    X = 0;
    Y = 0;
}

inline Vector2::Vector2(int Tx, int Ty): X(Tx), Y(Ty)
{
}

inline int Vector2::Size()
{
    return (int)X * (int)Y;
}
