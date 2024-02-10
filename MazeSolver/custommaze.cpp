/**
 * @file CustomMaze.cpp
 * @brief Implementation of the CustomMaze class methods.
 */

#include "custommaze.h"
#include "Cell.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CustomMaze::CustomMaze(string filePath) : filePath(filePath) {}

void CustomMaze::generateMaze() {
    try {
        ifstream file(filePath);

        string rows, columns, cellInfo;

        // Read the number of rows and columns from the file
        getline(file, rows);
        getline(file, columns);

        // Set maze dimensions based on the values read from the file
        height = stoi(rows);
        width = stoi(columns);

        // Construct the maze grid with cells
        for (unsigned short y = 0; y < height; y++) {
            maze.emplace_back();

            for (unsigned short x = 0; x < width; x++) {
                maze[y].emplace_back(new Cell(x, y));
            }
        }

        // Read cell information and update walls based on the file data
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                getline(file, cellInfo);

                stringstream stream(cellInfo);
                string value;

                vector<int> splittedCellInfo;

                // Split cell information into individual values
                while (getline(stream, value, ' ')) {
                    splittedCellInfo.push_back(stoi(value));
                }

                // Update walls in the cell based on the file data
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

        // Set the start and finish cells of the maze
        startCell = maze[0][0];
        finishCell = maze[height - 1][width - 1];

        file.close();
    }
    catch (const exception& e) {
        // Handle exceptions and print an error message
        cout << e.what();
    }
}
