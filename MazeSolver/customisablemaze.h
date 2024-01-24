#ifndef CUSTOMISABLEMAZE_H
#define CUSTOMISABLEMAZE_H

#include "maze.h"

class CustomisableMaze : public Maze
{
public:
    CustomisableMaze(unsigned short width, unsigned short height);

    bool addWallCoords(int x, int y);
    bool addPathCoords(int x, int y);
    void setWidth(unsigned short width);
    void setHeight(unsigned short height);
    void setStartCoords(int x, int y);
    void setFinishCoords(int x, int y);
};

#endif // CUSTOMISABLEMAZE_H
