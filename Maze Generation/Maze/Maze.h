#pragma once

#include <vector>
#include <stack>
#include <string>

#include "../Cell/Cell.h"

typedef std::vector<std::vector<Cell>> CellStorage;

class Maze
{
public:
    Maze() = default;
    Maze(Vector2 mazeSize, int seed);
    
    Cell MoveUpperCell(Cell current);
    Cell MoveLowerCell(Cell current);
    Cell MoveLeftCell(Cell current);
    Cell MoveRightCell(Cell current);

    Vector2 mazeSize;
    CellStorage Cells;
};
