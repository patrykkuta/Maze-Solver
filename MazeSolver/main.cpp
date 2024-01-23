#include "mainwindow.h"
#include "randomizedmaze.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>

#include <QApplication>

class CustomRectItem : public QGraphicsRectItem {
public:
    CustomRectItem(int x, int y, int width, int height, const vector<Wall> walls)
            : QGraphicsRectItem(x, y, width, height), walls(walls) {}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->setBrush(Qt::white);
        painter->setPen(Qt::NoPen);

        // Draw the rectangle without specific borders
        painter->drawRect(rect());

        for (Wall wall: walls) {
            if (wall == Wall::NORTH) {
                painter->setPen(Qt::black); // Set the color for the top border
                painter->drawLine(rect().topLeft(), rect().topRight());
            }
            else if (wall == Wall::SOUTH) {
                painter->setPen(Qt::black); // Set the color for the bottom border
                painter->drawLine(rect().bottomLeft(), rect().bottomRight());
            }
            else if (wall == Wall::WEST) {
                painter->setPen(Qt::black); // Set the color for the left border
                painter->drawLine(rect().topLeft(), rect().bottomLeft());
            }
            else if (wall == Wall::EAST) {
                painter->setPen(Qt::black); // Set the color for the right border
                painter->drawLine(rect().topRight(), rect().bottomRight());
            }
        }
    }
private:
    vector<Wall> walls;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    RandomizedMaze maze = RandomizedMaze(5, 5, 0.1);

    const int cellSize = 30;

    for (int y = 0; y < maze.getHeight(); y++) {
        for (int x = 0; x < maze.getWidth(); x++) {
            CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, maze.getMaze()[x][y].getWalls());

            // Add the item to the scene
            scene.addItem(rect);

        }
    }

    QGraphicsView view(&scene);
    view.show();

//    MainWindow w;
//    w.show();

    return a.exec();
}
