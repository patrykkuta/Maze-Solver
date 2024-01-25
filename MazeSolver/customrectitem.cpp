#include "customrectitem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>

#include <QApplication>

CustomRectItem::CustomRectItem(int x, int y, int width, int height, QColor color, const Cell &cell)
    : QGraphicsRectItem(x, y, width, height), color(color), cell(cell) {
}

void CustomRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setBrush(color);
    painter->setPen(Qt::NoPen);

    QColor penColor = QApplication::palette().color(QPalette::WindowText);
    int penSize = 3;

    // Draw the rectangle without specific borders
    painter->drawRect(rect());

    for (Wall wall: cell.getWalls()) {
        if (wall == Wall::NORTH) {
            painter->setPen(QPen(penColor, penSize)); // Set the color for the top border
            painter->drawLine(rect().topLeft(), rect().topRight());
        }
        else if (wall == Wall::SOUTH) {
            painter->setPen(QPen(penColor, penSize)); // Set the color for the bottom border
            painter->drawLine(rect().bottomLeft(), rect().bottomRight());
        }
        else if (wall == Wall::WEST) {
            painter->setPen(QPen(penColor, penSize)); // Set the color for the left border
            painter->drawLine(rect().topLeft(), rect().bottomLeft());
        }
        else if (wall == Wall::EAST) {
            painter->setPen(QPen(penColor, penSize)); // Set the color for the right border
            painter->drawLine(rect().topRight(), rect().bottomRight());
        }
    }
}

void CustomRectItem::setBackgroundColor(QColor c) {
    color = c;
    update();
}

void CustomRectItem::setCell(Cell& newCell) {
    cell = newCell;
    update();
}

Cell* CustomRectItem::getCell() {
    return &cell;
}
