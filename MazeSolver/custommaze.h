#ifndef CUSTOMMAZE_H
#define CUSTOMMAZE_H

#include "maze.h"
#include <string>

class CustomMaze : public Maze
{
private:
    string filePath;
    void generateMaze() override;

public:
   CustomMaze(string filePath);
};

#endif // CUSTOMMAZE_H
