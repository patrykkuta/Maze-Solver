#ifndef CUSTOMRECTITEM_H
#define CUSTOMRECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>
#include "Cell.h"
#include <QApplication>

class CustomRectItem : public QGraphicsRectItem {
public:
    CustomRectItem(int x, int y, int width, int height, QColor color, const Cell &cell, const QString& text, bool displayText);
    void setColor(QColor c);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    Cell cell;
    QColor color;
    QGraphicsTextItem *textItem;
    bool displayText;
};

#endif // CUSTOMRECTITEM_H
