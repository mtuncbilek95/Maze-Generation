#pragma once

#include <iostream>

enum class Direction : uint8_t
{
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3
};

enum class WallState : uint8_t
{
    ClosedState = 0,
    OpenState = 1,
};