#include "randomizedmaze.h"

RandomizedMaze::RandomizedMaze(unsigned short width, unsigned short height, double complexity) : Maze(width, height, complexity) {
    startCell = randomStart();
    finishCell = randomFinish();

    generateMaze();
}

Cell* RandomizedMaze::randomStart() {
    mt19937 gen(rd());

    uniform_int_distribution<unsigned short> distributionX(0, getWidth() - 1);
    unsigned short x = distributionX(gen);

    uniform_int_distribution<unsigned short> distributionY(0, getHeight() - 1);
    unsigned short y = distributionY(gen);

    return new Cell(x, y);
}

Cell* RandomizedMaze::randomFinish() {
    return randomStart();
}

void RandomizedMaze::generateMaze() {

    maze.reserve(height * width);

    for (unsigned short y = 0; y < height; y++) {
        maze.emplace_back();

        for (unsigned short x = 0; x < width; x++) {
            maze[y].emplace_back(x, y);
        }
    }

    Cell* randomCell = randomStart();
    Cell* startingCell = &maze[randomCell->getY()][randomCell->getX()];

    frontier.push_back(startingCell);

    while (!frontier.empty()) {
        unsigned short index = randomFrontierPosition();

        Cell* c = frontier[index];
        frontier.erase(frontier.begin() + index);

        c->visit();

        addUnvisitedNeighbours(c);

        // Connect with some opened cell
        connect(c);

    }

    delete randomCell;
}

void RandomizedMaze::addUnvisitedNeighbours(Cell* cell) {
    std::vector<Cell*> neighbors;

    if ((cell->getX() > 0) && !maze[cell->getY()][cell->getX() - 1].wasVisited()) {
        neighbors.push_back(&maze[cell->getY()][cell->getX() - 1]);
    }

    if ((cell->getX() < width - 1) && !maze[cell->getY()][cell->getX() + 1].wasVisited()) {
        neighbors.push_back(&maze[cell->getY()][cell->getX() + 1]);
    }

    if ((cell->getY() > 0) && !maze[cell->getY() - 1][cell->getX()].wasVisited()) {
        neighbors.push_back(&maze[cell->getY() - 1][cell->getX()]);
    }

    if ((cell->getY() < height - 1) && !maze[cell->getY() + 1][cell->getX()].wasVisited()) {
        neighbors.push_back(&maze[cell->getY() + 1][cell->getX()]);
    }

    // Shuffle the neighbors randomly
    std::mt19937 gen(rd());
    std::shuffle(neighbors.begin(), neighbors.end(), gen);

    // Add the shuffled neighbors to the frontier
    for (Cell* neighbor : neighbors) {
        frontier.push_back(neighbor);
    }
}

unsigned short RandomizedMaze::randomFrontierPosition() {
    mt19937 gen(rd());

    uniform_int_distribution<unsigned short> dist(0, frontier.size() - 1);
    unsigned short index = dist(gen);

    return index;
}

void RandomizedMaze::connect(Cell* cell) {
    // Generate a random order to check neighbors
    vector<Wall> w = {
            Wall::NORTH,
            Wall::SOUTH,
            Wall::WEST,
            Wall::EAST
    };

    shuffle(w.begin(), w.end(), rd);

    if (w.front() == Wall::NORTH) {
        if ((cell->getY() > 0) && maze[cell->getY() - 1][cell->getX()].wasVisited() && maze[cell->getY() - 1][cell->getX()].getWalls().size() > 1) {
            cell->removeWall(Wall::NORTH);
            maze[cell->getY() - 1][cell->getX()].removeWall(Wall::SOUTH);
        }
    }
    else if (w.front() == Wall::SOUTH) {
        if (cell->getY() < height - 1 && maze[cell->getY() + 1][cell->getX()].wasVisited() && maze[cell->getY() + 1][cell->getX()].getWalls().size() > 1) {
            cell->removeWall(Wall::SOUTH);
            maze[cell->getY() + 1][cell->getX()].removeWall(Wall::NORTH);
        }
    }
    else if (w.front() == Wall::WEST) {
        if (cell->getX() > 0 && maze[cell->getY()][cell->getX() - 1].wasVisited() && maze[cell->getY()][cell->getX() - 1].getWalls().size() > 1) {
            cell->removeWall(Wall::WEST);
            maze[cell->getY()][cell->getX() - 1].removeWall(Wall::EAST);
        }
    }
    else if (w.front() == Wall::EAST) {
        if (cell->getX() < width - 1 && maze[cell->getY()][cell->getX() + 1].wasVisited() && maze[cell->getY()][cell->getX() + 1].getWalls().size() > 1) {
            cell->removeWall(Wall::EAST);
            maze[cell->getY()][cell->getX() + 1].removeWall(Wall::WEST);
        }
    }
}