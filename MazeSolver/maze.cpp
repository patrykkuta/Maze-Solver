#include "maze.h"

Maze::Maze(unsigned short width, unsigned short height, double complexity) :
    width(width),
    height(height),
    complexity(complexity) {}

Maze::~Maze() {
    maze.clear();
    delete startCell;
    delete finishCell;
}

unsigned short Maze::getWidth() {return width;}

unsigned short Maze::getHeight() {return height;}

double Maze::getComplexity() {return complexity;}

vector<vector<Cell>> Maze::getMaze() {return maze;}

