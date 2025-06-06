#include "randomizedprimsalgorithm.h"

RandomizedPrimsAlgorithm::RandomizedPrimsAlgorithm(unsigned short width, unsigned short height) : GeneratingAlgorithm(width, height) {}

RandomizedPrimsAlgorithm::~RandomizedPrimsAlgorithm() {}

Cell* RandomizedPrimsAlgorithm::getGenerationStartCell() {
    mt19937 gen(rd());

    uniform_int_distribution<unsigned short> distributionX(0, mazeWidth - 1);
    unsigned short x = distributionX(gen);

    uniform_int_distribution<unsigned short> distributionY(0, mazeHeight - 1);
    unsigned short y = distributionY(gen);

    return new Cell(x, y);
}

vector<vector<Cell*>> RandomizedPrimsAlgorithm::generate() {

    Cell* randomCell = getGenerationStartCell();
    Cell* startingCell = maze[randomCell->getY()][randomCell->getX()];

    frontier.insert(startingCell);

    while (!frontier.empty()) {
        unsigned short index = randomFrontierPosition();

        auto item = next(frontier.begin(), index);
        Cell* cell = *item;

        Step step(State::CURRENT, cell);
        steps.push_back(step);

        frontier.erase(item);

        cell->visit();

        addUnvisitedNeighbours(cell);

        // Connect with some visited cell
        connect(cell);
    }

    delete randomCell;
    return maze;
}

unsigned short RandomizedPrimsAlgorithm::randomFrontierPosition() {
    mt19937 gen(rd());

    uniform_int_distribution<unsigned short> dist(0, frontier.size() - 1);
    unsigned short index = dist(gen);

    return index;
}

void RandomizedPrimsAlgorithm::addUnvisitedNeighbours(Cell* cell) {
    if ((cell->getX() > 0) && !maze[cell->getY()][cell->getX() - 1]->wasVisited()) {
        frontier.insert(maze[cell->getY()][cell->getX() - 1]);

        Step step(State::NEIGHBOUR, maze[cell->getY()][cell->getX() - 1]);
        if (find(steps.begin(), steps.end(), step) == steps.end()) {
            steps.push_back(step);
        }
    }

    if ((cell->getX() < mazeWidth - 1) && !maze[cell->getY()][cell->getX() + 1]->wasVisited()) {
        frontier.insert(maze[cell->getY()][cell->getX() + 1]);

        Step step(State::NEIGHBOUR, maze[cell->getY()][cell->getX() + 1]);
        if (find(steps.begin(), steps.end(), step) == steps.end()) {
            steps.push_back(step);
        }
    }

    if ((cell->getY() > 0) && !maze[cell->getY() - 1][cell->getX()]->wasVisited()) {
        frontier.insert(maze[cell->getY() - 1][cell->getX()]);

        Step step(State::NEIGHBOUR, maze[cell->getY() - 1][cell->getX()]);
        if (find(steps.begin(), steps.end(), step) == steps.end()) {
            steps.push_back(step);
        }
    }

    if ((cell->getY() < mazeHeight - 1) && !maze[cell->getY() + 1][cell->getX()]->wasVisited()) {
        frontier.insert(maze[cell->getY() + 1][cell->getX()]);

        Step step(State::NEIGHBOUR, maze[cell->getY() + 1][cell->getX()]);
        if (find(steps.begin(), steps.end(), step) == steps.end()) {
            steps.push_back(step);
        }
    }
}
