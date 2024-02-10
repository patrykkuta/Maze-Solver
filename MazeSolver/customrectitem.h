/**
 * @file CustomRectItem.h
 * @brief Declaration of the CustomRectItem class, a QGraphicsRectItem representing a cell in a maze.
 */
#ifndef CUSTOMRECTITEM_H
#define CUSTOMRECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QColor>
#include "Cell.h"

/**
 * @class CustomRectItem
 * @brief Represents a custom rectangle item in a QGraphicsScene, corresponding to a maze cell.
 */
class CustomRectItem : public QGraphicsRectItem {
public:
    /**
     * @brief Constructor for the CustomRectItem class.
     * @param x The x-coordinate of the rectangle.
     * @param y The y-coordinate of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @param color The color of the rectangle.
     * @param cell The corresponding maze cell.
     */
    CustomRectItem(int x, int y, int width, int height, QColor color, const Cell &cell);

    /**
     * @brief Sets the background color of the rectangle.
     * @param c The color to set as the background color.
     */
    void setBackgroundColor(QColor c);

    /**
     * @brief Sets the associated maze cell for the rectangle.
     * @param newCell The new maze cell to associate with the rectangle.
     */
    void setCell(Cell& newCell);

    /**
     * @brief Gets a pointer to the associated maze cell.
     * @return A pointer to the associated maze cell.
     */
    Cell* getCell();

protected:
    /**
     * @brief Paints the rectangle item, drawing the background and cell borders (walls).
     * @param painter The QPainter object for painting.
     * @param option The style options for the item.
     * @param widget The widget to paint on, default is nullptr.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    Cell cell; /**< The associated maze cell. */
    QColor color; /**< The background color of the rectangle. */
    QGraphicsTextItem *textItem; /**< A text item to display additional information (if needed). */
    bool displayText; /**< Flag indicating whether to display additional text. */
};

#endif // CUSTOMRECTITEM_H
