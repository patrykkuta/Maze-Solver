#include "custommaze.h"
#include "Cell.h"
#include <iostream>
#include <fstream>
#include <sstream>

CustomMaze::CustomMaze(string filePath) : filePath(filePath) {}

void CustomMaze::generateMaze() {
    try {
        ifstream file(filePath);

        string rows, columns, cellInfo;

        getline(file, rows);
        getline(file, columns);

        height = stoi(rows);
        width = stoi(columns);

        for (unsigned short y = 0; y < height; y++) {
            maze.emplace_back();

            for (unsigned short x = 0; x < width; x++) {
                maze[y].emplace_back(new Cell(x, y));
            }
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                getline(file, cellInfo);

                stringstream stream(cellInfo);
                string value;

                vector<int> splittedCellInfo;

                while (getline(stream, value, ' ')) {
                    splittedCellInfo.push_back(stoi(value));
                }

                if (!splittedCellInfo[2]) {
                    maze[splittedCellInfo[1]][splittedCellInfo[0]]->removeWall(Wall::NORTH);
                }
                if (!splittedCellInfo[3]) {
                    maze[splittedCellInfo[1]][splittedCellInfo[0]]->removeWall(Wall::SOUTH);
                }
                if (!splittedCellInfo[4]) {
                    maze[splittedCellInfo[1]][splittedCellInfo[0]]->removeWall(Wall::WEST);
                }
                if (!splittedCellInfo[5]) {
                    maze[splittedCellInfo[1]][splittedCellInfo[0]]->removeWall(Wall::EAST);
                }
            }
        }

        startCell = maze[0][0];
        finishCell = maze[height - 1][width - 1];

        file.close();
    }
    catch (const exception& e) {
        cout << e.what();
    }
}
