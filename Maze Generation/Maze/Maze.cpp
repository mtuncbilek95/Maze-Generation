#include "Maze.h"

Maze::Maze(Vector2 mazeSize, int seed)
{
    this->mazeSize = mazeSize;

    srand(seed);

    //  Initializing the matrix according to the mazeSize. After the initializing, next algorithm will fill all the info in the cell class.
    Cells.resize(mazeSize.Y);
    for (int yCoordinate = 0; yCoordinate < mazeSize.Y; yCoordinate++)
    {
        Cells.at(yCoordinate).resize(mazeSize.X);
        for (int xCoordinate = 0; xCoordinate < mazeSize.X; xCoordinate++)
        {
            Cell EmptyCell(Vector2(xCoordinate, yCoordinate));
            Cells.at(yCoordinate).at(xCoordinate) = EmptyCell;
        }
    }

    std::stack<Cell> VisitedCells;

    int visitedCount = 0;
    Vector2 location;

    //  While our visited cell count lower than the total cell count. Custom Geometry Vector library chooses the V(0,0) location for initial cell since there is no initialization.
    while (visitedCount < mazeSize.Size())
    {
        if (!Cells.at(location.Y).at(location.X).GetIsVisited())
        {
            Cells.at(location.Y).at(location.X).SetIsVisited(true);
            visitedCount++;
        }
        
        std::vector<Cell> NeighbourCells;

        /*
         *
         *  If the current Cell is not visited, system locates all the neighbours of the current looked cell via the functions below.
         * 
         */

        if (!MoveUpperCell(Cells.at(location.Y).at(location.X)).GetIsVisited())
            NeighbourCells.push_back(MoveUpperCell(Cells.at(location.Y).at(location.X)));
        if (!MoveLowerCell(Cells.at(location.Y).at(location.X)).GetIsVisited())
            NeighbourCells.push_back(MoveLowerCell(Cells.at(location.Y).at(location.X)));
        if (!MoveLeftCell(Cells.at(location.Y).at(location.X)).GetIsVisited())
            NeighbourCells.push_back(MoveLeftCell(Cells.at(location.Y).at(location.X)));
        if (!MoveRightCell(Cells.at(location.Y).at(location.X)).GetIsVisited())
            NeighbourCells.push_back(MoveRightCell(Cells.at(location.Y).at(location.X)));

        //  Break the walls according to recursive backingtrack DFS Algorithm. 
        if (!NeighbourCells.empty())
        {
            int randomNumber = rand() % NeighbourCells.size(); // 0 - N random number (N not included). For example: 0 >= x < 2
            VisitedCells.push(Cells.at(location.Y).at(location.X));

            if (NeighbourCells.at(randomNumber).GetLocation().X > Cells.at(location.Y).at(location.X).GetLocation().X)
            {
                Cells.at(NeighbourCells.at(randomNumber).GetLocation().Y).at(NeighbourCells.at(randomNumber).GetLocation().X).BreakTheWall(Direction::Left);
                Cells.at(location.Y).at(location.X).BreakTheWall(Direction::Right);
            }
            if (NeighbourCells.at(randomNumber).GetLocation().X < Cells.at(location.Y).at(location.X).GetLocation().X)
            {
                Cells.at(NeighbourCells.at(randomNumber).GetLocation().Y).at(NeighbourCells.at(randomNumber).GetLocation().X).BreakTheWall(Direction::Right);
                Cells.at(location.Y).at(location.X).BreakTheWall(Direction::Left);
            }
            if (NeighbourCells.at(randomNumber).GetLocation().Y > Cells.at(location.Y).at(location.X).GetLocation().Y)
            {
                Cells.at(NeighbourCells.at(randomNumber).GetLocation().Y).at(NeighbourCells.at(randomNumber).GetLocation().X).BreakTheWall(Direction::Up);
                Cells.at(location.Y).at(location.X).BreakTheWall(Direction::Down);
            }
            if (NeighbourCells.at(randomNumber).GetLocation().Y < Cells.at(location.Y).at(location.X).GetLocation().Y)
            {
                Cells.at(NeighbourCells.at(randomNumber).GetLocation().Y).at(NeighbourCells.at(randomNumber).GetLocation().X).BreakTheWall(Direction::Down);
                Cells.at(location.Y).at(location.X).BreakTheWall(Direction::Up);
            }

            // Move to the next room.
            location.X = NeighbourCells.at(randomNumber).GetLocation().X;
            location.Y = NeighbourCells.at(randomNumber).GetLocation().Y;
        }
        else
        {
            // If system stuck between visited rooms, return back till finding unvisited neighbour of the topped cell.
            Cell RecursiveBackingTrack = VisitedCells.top();
            VisitedCells.pop();
            location.X = RecursiveBackingTrack.GetLocation().X;
            location.Y = RecursiveBackingTrack.GetLocation().Y;
        }
    }

    // Turn all the cells visited to false to use this bool for PathFinder.
    for (int yCoordinate = 0; yCoordinate < Cells.size(); yCoordinate++)
    {
        for (int xCoordinate = 0; xCoordinate < Cells.at(yCoordinate).size(); xCoordinate++)
        {
            Cells.at(yCoordinate).at(xCoordinate).SetIsVisited(false);
        }
    }
}

Cell Maze::MoveUpperCell(Cell current)
{
    if (current.GetLocation().Y > 0) // Check if system look at the boundry cell.
    {
        return Cells.at(current.GetLocation().Y - 1).at(current.GetLocation().X);
    }
    else
    {
        return current;
    }
}

Cell Maze::MoveLowerCell(Cell current)
{
    if (current.GetLocation().Y < mazeSize.Y - 1) // Check if system look at the boundry cell.
    {
        return Cells.at(current.GetLocation().Y + 1).at(current.GetLocation().X);
    }
    else
    {
        return current;
    }
}

Cell Maze::MoveLeftCell(Cell current)
{
    if (current.GetLocation().X > 0) // Check if system look at the boundry cell.
    {
        return Cells.at(current.GetLocation().Y).at(current.GetLocation().X - 1);
    }
    else
    {
        return current;
    }
}

Cell Maze::MoveRightCell(Cell current)
{
    if (current.GetLocation().X < mazeSize.X - 1) // Check if system look at the boundry cell.
    {
        return Cells.at(current.GetLocation().Y).at(current.GetLocation().X + 1);
    }
    else
    {
        return current;
    }
}
