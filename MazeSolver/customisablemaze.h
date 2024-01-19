#ifndef CUSTOMISABLEMAZE_H
#define CUSTOMISABLEMAZE_H

#include "maze.h"

class CustomisableMaze : public Maze
{
public:
    CustomisableMaze(int width, int height, double complexity);

    bool addWallCoords(int x, int y);
    bool addPathCoords(int x, int y);
    void setWidth(int width);
    void setHeight(int height);
    void setComplexity(double complexity);
    void setStartCoords(int x, int y);
    void setFinishCoords(int x, int y);
};

#endif // CUSTOMISABLEMAZE_H
