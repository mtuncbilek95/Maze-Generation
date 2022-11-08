#include "StaticFunctions.h"

int main(int argc, char* argv[])
{
    if(argc < 3 || argc > 4){
        std::cout << "Invalid number of arguments." << std::endl;
        return 0;
    }
    Vector2 inputMazeSize;
    Vector2 startLocation;
    Vector2 endLocation;

    inputMazeSize.Y = std::stoi(argv[1]);
    endLocation.Y = std::stoi(argv[1]) - 1;
    inputMazeSize.X = std::stoi(argv[2]);
    endLocation.X = std::stoi(argv[2]) - 1;

    int seed = (int)time(NULL);
    if(argc == 4){
        seed = std::stoi(argv[3]);
    }
    Maze FirstMaze(inputMazeSize, seed);

    Cell StartCell(startLocation);
    Cell EndCell(endLocation);

    IndependentFunctions::PathFinder(FirstMaze, StartCell, EndCell);
    IndependentFunctions::PrintMaze(FirstMaze);

    return 0;
}