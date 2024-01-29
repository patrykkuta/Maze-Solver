#include "maze.h"

Maze::Maze(unsigned short width, unsigned short height) :
    width(width),
    height(height) {}

Maze::~Maze() {
    maze.clear();
    delete startCell;
    delete finishCell;
}

unsigned short Maze::getWidth() {return width;}

unsigned short Maze::getHeight() {return height;}

vector<vector<Cell*>> Maze::getMaze() {return maze;}

Cell* Maze::getStartCell() {return startCell;}

Cell* Maze::getFinishCell() {return finishCell;}

vector<Step> Maze::getGenerationSteps() {
    return generationSteps;
}

