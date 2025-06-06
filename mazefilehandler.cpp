#include "mazefilehandler.h"

MazeFileHandler::MazeFileHandler(string filePath) : filePath(filePath) {}

bool MazeFileHandler::saveMaze(Maze* maze) {
    try {
        ofstream file(filePath);

        // Write maze dimensions to the file
        file << maze->getHeight() << endl;
        file << maze->getWidth() << endl;

        // Write each cell's information to the file
        for (const vector<Cell*>& row : maze->getMaze()) {
            for (Cell* cell : row) {
                map<Wall, bool> walls = cell->getWalls();
                file << cell->getX() << " " << cell->getY() << " " << walls[Wall::NORTH] << " "
                     << walls[Wall::SOUTH] << " " << walls[Wall::WEST] << " " << walls[Wall::EAST] << endl;
            }
        }

        file.close();

        return true;
    } catch (exception e) {
        cout << e.what() << endl;
        return false;
    }
}
