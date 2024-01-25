#include "randomizedmaze.h"

RandomizedMaze::RandomizedMaze(unsigned short width, unsigned short height) : Maze(width, height) {

    for (unsigned short y = 0; y < height; y++) {
        maze.emplace_back();

        for (unsigned short x = 0; x < width; x++) {
            maze[y].emplace_back(new Cell(x, y));
        }
    }

    startCell = maze[0][0];
    finishCell = maze[height - 1][width - 1];

    // generateMaze();
}

RandomizedMaze::~RandomizedMaze() {
    // for (vector<Cell*>& row : maze) {
    //     for (Cell* cellPtr : row) {
    //         delete cellPtr;
    //     }
    // }
}

Cell* RandomizedMaze::getGenerationStartCell() {
    mt19937 gen(rd());

    uniform_int_distribution<unsigned short> distributionX(0, getWidth() - 1);
    unsigned short x = distributionX(gen);

    uniform_int_distribution<unsigned short> distributionY(0, getHeight() - 1);
    unsigned short y = distributionY(gen);

    return new Cell(x, y);
}

void RandomizedMaze::generateMaze() {

    Cell* rc = getGenerationStartCell();
    Cell* startingCell = maze[rc->getY()][rc->getX()];

    frontier.insert(startingCell);

    while (!frontier.empty()) {
        unsigned short index = randomFrontierPosition();

        auto item = next(frontier.begin(), index);
        Cell* c = *item;

        generationSteps.push(new Step(State::CURRENT, c));

        frontier.erase(item);

        c->visit();

        addUnvisitedNeighbours(c);

        // Connect with some opened cell
        connect(c);
    }

    delete rc;
}

void RandomizedMaze::addUnvisitedNeighbours(Cell* cell) {
    if ((cell->getX() > 0) && !maze[cell->getY()][cell->getX() - 1]->wasVisited()) {
        frontier.insert(maze[cell->getY()][cell->getX() - 1]);
        generationSteps.push(new Step(State::NEIGHBOUR, maze[cell->getY()][cell->getX() - 1]));
    }

    if ((cell->getX() < width - 1) && !maze[cell->getY()][cell->getX() + 1]->wasVisited()) {
        frontier.insert(maze[cell->getY()][cell->getX() + 1]);
        generationSteps.push(new Step(State::NEIGHBOUR, maze[cell->getY()][cell->getX() + 1]));
    }

    if ((cell->getY() > 0) && !maze[cell->getY() - 1][cell->getX()]->wasVisited()) {
        frontier.insert(maze[cell->getY() - 1][cell->getX()]);
        generationSteps.push(new Step(State::NEIGHBOUR, maze[cell->getY() - 1][cell->getX()]));
    }

    if ((cell->getY() < height - 1) && !maze[cell->getY() + 1][cell->getX()]->wasVisited()) {
        frontier.insert(maze[cell->getY() + 1][cell->getX()]);
        generationSteps.push(new Step(State::NEIGHBOUR, maze[cell->getY() + 1][cell->getX()]));
    }
}

unsigned short RandomizedMaze::randomFrontierPosition() {
    mt19937 gen(rd());

    uniform_int_distribution<unsigned short> dist(0, frontier.size() - 1);
    unsigned short index = dist(gen);

    return index;
}

bool RandomizedMaze::connect(Cell* cell) {

    if (cell->getY() < height - 1 && maze[cell->getY() + 1][cell->getX()]->wasVisited()) {
        cell->removeWall(Wall::SOUTH);
        maze[cell->getY() + 1][cell->getX()]->removeWall(Wall::NORTH);
        return true;
    }

    else if (cell->getX() > 0 && maze[cell->getY()][cell->getX() - 1]->wasVisited()) {
        cell->removeWall(Wall::WEST);
        maze[cell->getY()][cell->getX() - 1]->removeWall(Wall::EAST);
        return true;
    }

    else if (cell->getX() < width - 1 && maze[cell->getY()][cell->getX() + 1]->wasVisited()) {
        cell->removeWall(Wall::EAST);
        maze[cell->getY()][cell->getX() + 1]->removeWall(Wall::WEST);
        return true;
    }

    else if ((cell->getY() > 0) && maze[cell->getY() - 1][cell->getX()]->wasVisited()) {
        cell->removeWall(Wall::NORTH);
        maze[cell->getY() - 1][cell->getX()]->removeWall(Wall::SOUTH);
        return true;
    }

    return false;
}
