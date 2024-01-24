#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QResizeEvent>
#include "algorithm.h"
#include "customrectitem.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createMaze();
    void solveMaze();

private:
    Ui::MainWindow *ui;
    Maze* maze = nullptr;
    bool mazeCreated = false;
    vector<vector<CustomRectItem*>> rectItemCells;
    bool solving;
    vector<Cell*> steps;
    int animationSpeed;
    QTimer* timer = nullptr;

};
#endif // MAINWINDOW_H
