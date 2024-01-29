#ifndef MAZEFILEHANDLER_H
#define MAZEFILEHANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include "cell.h"
#include "maze.h"

using namespace std;

class MazeFileHandler
{
public:
    MazeFileHandler(string filePath);

    bool saveMaze(Maze *maze);

private:
    string filePath;

};
#endif // MAZEFILEHANDLER_H
