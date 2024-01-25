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
    bool solved;
    bool generating;
    int animationSpeed;
    QTimer* timerTraverseMaze = nullptr;
    QTimer* timerShowPath = nullptr;
    QTimer* timerMazeGeneration = nullptr;
    queue<Step*> solvingSteps;
    queue<Step*> generationSteps;
    vector<Cell*> solutionPath;
    Cell* lastCurrentSolve = nullptr;
    Cell* lastCurrentGenerate = nullptr;
    int visitedCellCount = 0;
    int pathLength = 0;

    void resetMaze();

};
#endif // MAINWINDOW_H
