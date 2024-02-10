/**
 * @file CustomRectItem.cpp
 * @brief Implementation of the CustomRectItem class methods.
 */

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

    // Set the background color of the rectangle
    painter->setBrush(color);

    // Draw the main rectangle without specific borders
    painter->setPen(Qt::NoPen);
    painter->drawRect(rect());

    // Retrieve the wall information from the associated maze cell
    map<Wall, bool> walls = cell.getWalls();

    // Set the color and size of the pen for drawing walls
    QColor penColor = QApplication::palette().color(QPalette::WindowText);
    double penSize = 2.2;
    QPen pen(penColor, penSize);

    // Draw the walls based on the cell's wall information
    if (walls[Wall::NORTH]) {
        painter->setPen(pen);
        painter->drawLine(rect().topLeft(), rect().topRight());
    }
    if (walls[Wall::SOUTH]) {
        painter->setPen(pen);
        painter->drawLine(rect().bottomLeft(), rect().bottomRight());
    }
    if (walls[Wall::WEST]) {
        painter->setPen(pen);
        painter->drawLine(rect().topLeft(), rect().bottomLeft());
    }
    if (walls[Wall::EAST]) {
        painter->setPen(pen);
        painter->drawLine(rect().topRight(), rect().bottomRight());
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
