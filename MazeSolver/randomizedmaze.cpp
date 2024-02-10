#include "randomizedmaze.h"

RandomizedMaze::RandomizedMaze(unsigned short width, unsigned short height, GeneratingAlgorithm* algorithm) : Maze(width, height, algorithm) {
    for (unsigned short y = 0; y < height; y++) {
        maze.emplace_back();

        for (unsigned short x = 0; x < width; x++) {
            maze[y].emplace_back(new Cell(x, y));
        }
    }
}

RandomizedMaze::~RandomizedMaze() {
    // for (vector<Cell*>& row : maze) {
    //     for (Cell* cellPtr : row) {
    //         delete cellPtr;
    //     }
    // }
}

void RandomizedMaze::generateMaze() {
    maze = generatingAlgorithm->generate();

    startCell = maze[0][0];
    finishCell = maze[height - 1][width - 1];
}
