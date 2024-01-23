#include "mainwindow.h"
#include "randomizedmaze.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>

#include <QApplication>

class CustomRectItem : public QGraphicsRectItem {
public:
    CustomRectItem(int x, int y, int width, int height, const vector<Wall> walls, const QString& text)
            : QGraphicsRectItem(x, y, width, height), walls(walls) {

        // Create a QGraphicsTextItem as a child of the CustomRectItem
        textItem = new QGraphicsTextItem(text, this);
        textItem->setDefaultTextColor(Qt::black);
        textItem->setPos(x + width / 4, y + height / 4); // Adjust the position as needed

    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        // Set the brush and other styles as needed
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
    QGraphicsTextItem *textItem;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    RandomizedMaze maze = RandomizedMaze(10, 10, 0.1);

    const int cellSize = 100;

    for (int y = 0; y < maze.getHeight(); y++) {
        for (int x = 0; x < maze.getWidth(); x++) {
            QString textInfo = QString("N:%1 S:%2\nW:%3 E:%4\nV:%5").arg(maze.getMaze()[x][y].walls.NORTH).arg(maze.getMaze()[x][y].walls.SOUTH).arg(maze.getMaze()[x][y].walls.WEST).arg(maze.getMaze()[x][y].walls.EAST).arg(maze.getMaze()[x][y].wasVisited());
            CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, maze.getMaze()[x][y].getWalls(), textInfo);

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
