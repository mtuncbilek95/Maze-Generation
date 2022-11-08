#pragma once

#include <Vector2.h>
#include <Enum.h>
#include <vector>

class Cell{
public:
    Cell() = default;
    Cell(Vector2 location);
    
    void BreakTheWall(Direction direction);
    void SetIsVisited(bool bValue);
    
    bool GetWallState(Direction direction);
    bool GetIsVisited();

    Vector2 GetLocation();


private:
    std::vector<WallState> Walls;
    bool bIsVisited;
    Vector2 centerLocation;
};
