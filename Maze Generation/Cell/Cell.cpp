#include "Cell.h"

Cell::Cell(Vector2 location)
{
    this->centerLocation = location;
    this->SetIsVisited(false);

    Walls.resize(4);

    for (int i = 0; i < Walls.size(); i++)
    {
        Walls.at(i) = WallState::ClosedState;
    }
}

void Cell::BreakTheWall(Direction direction)
{
    Walls.at((int)direction) = WallState::OpenState;
}

void Cell::SetIsVisited(bool bValue)
{
    bIsVisited = bValue;
}

bool Cell::GetWallState(Direction direction)
{
    return (int)Walls.at((int)direction);
}

bool Cell::GetIsVisited()
{
    return bIsVisited;
}

Vector2 Cell::GetLocation()
{
    return centerLocation;
}
