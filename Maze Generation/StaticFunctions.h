#pragma once

#include "Maze/Maze.h"

namespace IndependentFunctions
{
    void PrintMaze(Maze& PrintedMaze)
    {
        for (int x = 0; x < PrintedMaze.Cells.size(); x++)
        {
            for (int i = 0; i < 2; i++)
            {
                for (int y = 0; y < PrintedMaze.Cells.at(x).size(); y++)
                {
                    switch (i)
                    {
                    case 0:
                        if (PrintedMaze.Cells.at(x).at(y).GetWallState(Direction::Up))
                        {
                            std::cout << "+   ";
                        }
                        else
                        {
                            std::cout << "+---";
                        }
                        if (y == PrintedMaze.Cells.at(x).size() - 1)
                        {
                            std::cout << "+";
                        }
                        break;
                    case 1:
                        if (PrintedMaze.Cells.at(x).at(y).GetWallState(Direction::Left))
                        {
                            std::cout << " ";
                        }
                        else
                        {
                            std::cout << "|";
                        }
                        if (PrintedMaze.Cells.at(x).at(y).GetIsVisited())
                        {
                            std::cout << " . ";
                        }
                        else
                        {
                            std::cout << "   ";
                        }
                        if (y == PrintedMaze.Cells.at(x).size() - 1)
                        {
                            std::cout << "|";
                        }
                        break;
                    }
                }
                std::cout << std::endl;
            }
        }

        //  Close the Maze's bottom boundry.
        for (int i = 0; i < PrintedMaze.Cells.at(0).size(); i++)
        {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
    }

    bool PathFinder(Maze& UsedMaze, Cell& PreviousCell, Cell& NextCell)
    {
        UsedMaze.Cells[PreviousCell.GetLocation().Y][PreviousCell.GetLocation().X].SetIsVisited(true);

        if (PreviousCell.GetLocation().X == NextCell.GetLocation().X && PreviousCell.GetLocation().Y == NextCell.GetLocation().Y)
        {
            return true;
        }

        PreviousCell = UsedMaze.Cells[PreviousCell.GetLocation().Y][PreviousCell.GetLocation().X];

        std::vector<Cell> NeighborCells;

        if (PreviousCell.GetWallState(Direction::Left) && !UsedMaze.Cells[PreviousCell.GetLocation().Y][PreviousCell.GetLocation().X - 1].GetIsVisited())
        {
            NeighborCells.push_back(UsedMaze.Cells[PreviousCell.GetLocation().Y][PreviousCell.GetLocation().X - 1]);
        }
        if (PreviousCell.GetWallState(Direction::Right) && !UsedMaze.Cells[PreviousCell.GetLocation().Y][PreviousCell.GetLocation().X + 1].GetIsVisited())
        {
            NeighborCells.push_back(UsedMaze.Cells[PreviousCell.GetLocation().Y][PreviousCell.GetLocation().X + 1]);
        }
        if (PreviousCell.GetWallState(Direction::Up) && !UsedMaze.Cells[PreviousCell.GetLocation().Y - 1][PreviousCell.GetLocation().X].GetIsVisited())
        {
            NeighborCells.push_back(UsedMaze.Cells[PreviousCell.GetLocation().Y - 1][PreviousCell.GetLocation().X]);
        }
        if (PreviousCell.GetWallState(Direction::Down) && !UsedMaze.Cells[PreviousCell.GetLocation().Y + 1][PreviousCell.GetLocation().X].GetIsVisited())
        {
            NeighborCells.push_back(UsedMaze.Cells[PreviousCell.GetLocation().Y + 1][PreviousCell.GetLocation().X]);
        }
        

        for (int i = 0; i < NeighborCells.size(); i++)
        {
            if (PathFinder(UsedMaze, NeighborCells[i], NextCell))
            {
                return true;
            }
        }
        UsedMaze.Cells[PreviousCell.GetLocation().Y][PreviousCell.GetLocation().X].SetIsVisited(false);

        return false;
    }
}