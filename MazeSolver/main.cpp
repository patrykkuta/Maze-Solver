#include "randomizedmaze.h"
#include "customrectitem.h"
#include "breadthfirstsearch.h"
#include "mainwindow.h"

#include <iostream>
#include <vector>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QGraphicsScene scene;
    // QGraphicsView view(&scene);

    // RandomizedMaze maze = RandomizedMaze(4, 4);

    // const int cellSize = 40;

    // vector<vector<CustomRectItem*>> cells;

    // for (int y = 0; y < maze.getWidth(); y++) {
    //     cells.emplace_back();
    //     for (int x = 0; x < maze.getHeight(); x++) {
    //         Cell* current = maze.getMaze()[x][y];
    //         QColor color(255, 255, 255);

    //         if (*current == *maze.getStartCell()) color.setRgb(144,238,144);
    //         else if (*current == *maze.getFinishCell()) color.setRgb(250,128,114);

    //         QString textInfo = QString("(%1, %2)").arg(y).arg(x);
    //         CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, color, *current, textInfo);
    //         cells[y].push_back(rect);

    //         // Add the item to the scene
    //         scene.addItem(rect);

    //     }
    // }

    // view.show();

    // BreadthFirstSearch algorithm = BreadthFirstSearch();

    // for(Cell* cell: algorithm.solve(maze)) {
    //     cells[cell->getX()][cell->getY()]->setColor(QColor(210, 210, 210));
    // }



    MainWindow w;
    w.show();


    return a.exec();
}
