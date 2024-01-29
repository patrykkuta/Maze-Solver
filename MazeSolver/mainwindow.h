#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QResizeEvent>
#include "pathfindingalgorithm.h"
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
    void drawMaze();
    void solveMaze();
    void createNewWindow();

private:
    struct {
        const QColor VISITED = QColor(222, 222, 222);
        const QColor START = QColor(144,238,144);
        const QColor FINISH = QColor(255,0,0);
        const QColor CURRENT = QApplication::palette().color(QPalette::Highlight);
        const QColor EMPTY = QApplication::palette().color(QPalette::Base);
        const QColor NEIGHBOUR = QColor(250, 128, 114);
    } colours;

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
    vector<Step> generationSteps;
    vector<Cell*> solutionPath;
    Cell* lastCurrentSolve = nullptr;
    Cell* lastCurrentGenerate = nullptr;
    int visitedCellCount = 0;
    int pathLength = 0;

    void resetMaze();

};
#endif // MAINWINDOW_H
