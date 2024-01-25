#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "randomizedmaze.h"
#include "customrectitem.h"
#include "breadthfirstsearch.h"
#include "depthfirstsearch.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(createMaze()));
    connect(ui->solveButton, SIGNAL(clicked()), this, SLOT(solveMaze()));
    connect(ui->exitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    connect(ui->animationSpeedSlider, &QSlider::valueChanged, [=]() {

        animationSpeed = ui->animationSpeedSlider->value();

        ui->animationSpeedLabel->setText(QString("Speed: " + QString::number(animationSpeed) + " (cells per second)"));

        if(timerTraverseMaze != nullptr) {
            timerTraverseMaze->setInterval(1000 / animationSpeed);
        }

        if(timerMazeGeneration != nullptr) {
            timerMazeGeneration->setInterval(1000 / animationSpeed);
        }
    });
    connect(ui->bfsRButton, &QRadioButton::toggled, [=](bool checked) {
        if (checked && solved) {
            solved = false;
        }
    });
    connect(ui->dfsRButton, &QRadioButton::toggled, [=](bool checked) {
        if (checked && solved) {
            solved = false;
        }
    });

    animationSpeed = ui->animationSpeedSlider->value();
}

MainWindow::~MainWindow()
{
    delete timerTraverseMaze;
    delete timerShowPath;
    delete timerMazeGeneration;
    delete ui->mazeView->scene();
    delete maze;
    delete ui;
}

void MainWindow::createMaze() {
    if(!solving && !generating) {
        if (maze != nullptr) {
            delete maze;
        }

        if (ui->mazeView->scene()) {
            delete ui->mazeView->scene();
        }

        mazeCreated = false;
        generating = true;
        rectItemCells.clear();
        solving = false;
        solved = false;
        pathLength = 0;
        visitedCellCount = 0;
        ui->visitedCellsLabel->setText(QString("Visited cells: 0"));
        ui->pathLengthLabel->setText(QString("Path length: 0"));

        QGraphicsScene* mazeScene = new QGraphicsScene(this);

        // Not generated maze
        maze = new RandomizedMaze(ui->rowsCount->value(), ui->columnsCount->value());

        int cellSize = qMin(ui->mazeView->width() / maze->getWidth(), ui->mazeView->height() / maze->getHeight()) - 5/maze->getMaze().size();

        // Display not generated maze
        for (int y = 0; y < maze->getWidth(); y++) {
            rectItemCells.emplace_back();
            for (int x = 0; x < maze->getHeight(); x++) {
                Cell* current = maze->getMaze()[x][y];
                QColor color = QApplication::palette().color(QPalette::Base);

                CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, color, *current);
                rectItemCells[y].push_back(rect);

                // Add the item to the scene
                mazeScene->addItem(rect);
            }
        }

        ui->mazeView->setScene(mazeScene);

        // Generate maze
        maze->generateMaze();

        generationSteps = maze->getGenerationSteps();

        timerMazeGeneration = new QTimer(this);

        connect(timerMazeGeneration, &QTimer::timeout, [=]() {
            if (!generationSteps.empty()) {
                Step* step = generationSteps.front();

                if (step->getStep().first == State::CURRENT && lastCurrentGenerate == nullptr) {
                    lastCurrentGenerate = step->getStep().second;

                    rectItemCells[step->getStep().second->getX()][step->getStep().second->getY()]->setCell(*step->getStep().second);
                    rectItemCells[step->getStep().second->getX()][step->getStep().second->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight)); // Color as current
                }
                else if (step->getStep().first == State::CURRENT && lastCurrentGenerate != nullptr) {
                    rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setCell(*lastCurrentGenerate);
                    rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Base)); // Color as visited

                    rectItemCells[step->getStep().second->getX()][step->getStep().second->getY()]->setCell(*step->getStep().second);
                    rectItemCells[step->getStep().second->getX()][step->getStep().second->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight)); // Color as current

                    lastCurrentGenerate = step->getStep().second;
                }
                else if (step->getStep().first == State::NEIGHBOUR) {
                    rectItemCells[step->getStep().second->getX()][step->getStep().second->getY()]->setBackgroundColor(QColor(250, 128, 114)); // Color as neighbour
                }

                generationSteps.pop();
            }
            else {
                timerMazeGeneration -> stop();
                mazeCreated = true;
                generating = false;

                rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Base)); // Color as visited
                rectItemCells[maze->getStartCell()->getX()][maze->getStartCell()->getY()]->setBackgroundColor(QColor(144,238,144)); // Color start cell
                rectItemCells[maze->getFinishCell()->getX()][maze->getFinishCell()->getY()]->setBackgroundColor(QColor(255,0,0)); // Color finish cell

                lastCurrentGenerate = nullptr;
            }
        });

        timerMazeGeneration->start(1000 / animationSpeed);
    }
}

void MainWindow::solveMaze() {
    if (mazeCreated && !generating && !solving && !solved) {

        solving = true;
        resetMaze();

        Algorithm* algorithm = nullptr;

        for (QRadioButton* rb: ui->solveMethodGroupBox->findChildren<QRadioButton*>()) {
            if(rb->isChecked()) {
                if (rb->text() == "Breadth-First Search Algorithm") {
                    algorithm = new BreadthFirstSearch();
                }
                 else if(rb->text() == "Depth-First Search Algorithm") {
                     algorithm = new DepthFirstSearch();
                 }
            }
        }

        algorithm->solve(*maze);
        solvingSteps = algorithm->getSteps();
        solutionPath = algorithm->getSolutionPath();

        timerTraverseMaze = new QTimer(this);
        timerShowPath = new QTimer(this);

        connect(timerTraverseMaze, &QTimer::timeout, [=]() {
            if (!solvingSteps.empty()) {
                Step* step = solvingSteps.front();

                if(step->getStep().second != maze->getStartCell() && step ->getStep().second != maze->getFinishCell()) {

                    if (step->getStep().first == State::CURRENT && lastCurrentSolve == nullptr) {
                        lastCurrentSolve = step->getStep().second;

                        rectItemCells[step->getStep().second->getX()][step->getStep().second->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight));
                        ui->visitedCellsLabel->setText(QString("Visited cells: " + QString::number(++visitedCellCount)));
                    }
                    else if (step->getStep().first == State::CURRENT && lastCurrentSolve != nullptr) {
                        rectItemCells[lastCurrentSolve->getX()][lastCurrentSolve->getY()]->setBackgroundColor(QColor(222, 222, 222)); // Color as visited
                        rectItemCells[step->getStep().second->getX()][step->getStep().second->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight));

                        lastCurrentSolve = step->getStep().second;

                        ui->visitedCellsLabel->setText(QString("Visited cells: " + QString::number(++visitedCellCount)));
                    }
                    else if (step->getStep().first == State::NEIGHBOUR) {
                        rectItemCells[step->getStep().second->getX()][step->getStep().second->getY()]->setBackgroundColor(QColor(250, 128, 114));
                    }

                }
                else if (step ->getStep().second == maze->getFinishCell()) {
                    rectItemCells[lastCurrentSolve->getX()][lastCurrentSolve->getY()]->setBackgroundColor(QColor(222, 222, 222)); // Color as visited
                }

                solvingSteps.pop();
            }
            else {
                timerTraverseMaze->stop();
                timerTraverseMaze = nullptr;
                lastCurrentSolve = nullptr;

                connect(timerShowPath, &QTimer::timeout, [=]() {
                    if (!solutionPath.empty()) {
                        Cell* cell = solutionPath.at(0);

                        if (cell != maze->getStartCell() && cell != maze->getFinishCell()) {
                            rectItemCells[cell->getX()][cell->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight)); // Color as visited
                            rectItemCells[cell->getX()][cell->getY()]->update();
                        }

                        ui->pathLengthLabel->setText(QString("Path length: " + QString::number(++pathLength)));
                        solutionPath.erase(solutionPath.begin());
                    }
                    else {
                        timerShowPath -> stop();
                        timerShowPath = nullptr;

                        solving = false;
                        solved = true;
                    }
                });

                timerShowPath->start(500 / solutionPath.size());
            }
        });

        timerTraverseMaze->start(1000 / animationSpeed);

        delete algorithm;
    }
}

void MainWindow::resetMaze() {
    for(vector<CustomRectItem*>& row: rectItemCells) {
        for (CustomRectItem* cell: row) {
            if (*cell->getCell() != *maze->getStartCell() && *cell->getCell() != *maze->getFinishCell()) {
                cell->setBackgroundColor(QApplication::palette().color(QPalette::Base));
            }
        }
    }

    visitedCellCount = 0;
    pathLength = 0;
    ui->visitedCellsLabel->setText(QString("Visited cells: 0"));
    ui->pathLengthLabel->setText(QString("Path length: 0"));
}