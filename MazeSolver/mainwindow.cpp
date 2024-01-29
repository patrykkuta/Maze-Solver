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

    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(drawMaze()));
    connect(ui->solveButton, SIGNAL(clicked()), this, SLOT(solveMaze()));
    connect(ui->exitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    connect(ui->animationSpeedSlider, &QSlider::valueChanged, [=](int value) {

        animationSpeed = value;

        ui->animationSpeedLabel->setText(QString("Speed: " + QString::number(animationSpeed) + " (cells per second)"));

        if(timerTraverseMaze != nullptr) {
            timerTraverseMaze->setInterval(1000.0 / animationSpeed);
        }

        if(timerMazeGeneration != nullptr) {
            timerMazeGeneration->setInterval(1000.0 / animationSpeed);
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

    connect(ui->zoomSlider, &QSlider::valueChanged, [=](int value) {
        double scaleFactor;

        if (value > 0) {
            scaleFactor = 1 + value / 20.0;
        }
        else {
            scaleFactor = 1 + value / 100.0;
        }

        ui->mazeView->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
        ui->zoomLabel->setText(QString("Zoom: " + QString::number(scaleFactor) + "x"));


    });
    connect(ui->zoomSlider, &QSlider::sliderMoved, [=](int value) {
        double scaleFactor;

        if (value > 0) {
            scaleFactor = 1 + value / 20.0;
        }
        else {
            scaleFactor = 1 + value / 100.0;
        }

        ui->mazeView->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
        ui->zoomLabel->setText(QString("Zoom: " + QString::number(scaleFactor) + "x"));
    });
    connect(ui->animationPlayButton, &QPushButton::clicked, [=]() {
        if(timerTraverseMaze != nullptr) {
            if(timerTraverseMaze->isActive()) {
                ui->statusbar->showMessage(QString("Solving paused."));
                ui->animationPlayButton->setText(QString("Resume"));
                timerTraverseMaze->stop();
            }
            else {
                ui->statusbar->showMessage(QString("Solving maze..."));
                ui->animationPlayButton->setText(QString("Pause"));
                timerTraverseMaze->start();
            }
        }

        else if(timerMazeGeneration != nullptr) {
            if(timerMazeGeneration->isActive()) {
                ui->statusbar->showMessage(QString("Generating paused."));
                ui->animationPlayButton->setText(QString("Resume"));
                timerMazeGeneration->stop();
            }
            else {
                ui->statusbar->showMessage(QString("Generating maze..."));
                ui->animationPlayButton->setText(QString("Pause"));
                timerMazeGeneration->start();
            }
        }

        else if (timerShowPath != nullptr) {
            if(timerShowPath->isActive()) {
                ui->statusbar->showMessage(QString("Finding paused."));
                ui->animationPlayButton->setText(QString("Resume"));
                timerShowPath->stop();
            }
            else {
                ui->statusbar->showMessage(QString("Finding path..."));
                ui->animationPlayButton->setText(QString("Pause"));
                timerShowPath->start();
            }
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

void MainWindow::drawMaze() {
    if(!solving && !generating) {
        if (maze != nullptr) {
            delete maze;
        }

        if (ui->mazeView->scene()) {
            delete ui->mazeView->scene();
        }

        ui->statusbar->showMessage(QString("Generating maze..."));

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
                Step* step = &generationSteps.at(0);

                if (step->state() == State::CURRENT && lastCurrentGenerate == nullptr) {
                    lastCurrentGenerate = step->cell();

                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setCell(*step->cell());
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight)); // Color as current
                }
                else if (step->state() == State::CURRENT && lastCurrentGenerate != nullptr) {
                    rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setCell(*lastCurrentGenerate);
                    rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Base)); // Color as visited

                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setCell(*step->cell());
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight)); // Color as current

                    lastCurrentGenerate = step->cell();
                }
                else if (step->state() == State::NEIGHBOUR) {
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(QColor(250, 128, 114)); // Color as neighbour
                }

                generationSteps.erase(generationSteps.begin());

            }
            else {
                timerMazeGeneration -> stop();
                mazeCreated = true;
                generating = false;
                timerMazeGeneration = nullptr;

                rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Base)); // Color as visited
                rectItemCells[maze->getStartCell()->getX()][maze->getStartCell()->getY()]->setBackgroundColor(QColor(144,238,144)); // Color start cell
                rectItemCells[maze->getFinishCell()->getX()][maze->getFinishCell()->getY()]->setBackgroundColor(QColor(255,0,0)); // Color finish cell

                ui->statusbar->showMessage(QString("Maze successfully generated."));

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

        ui->statusbar->showMessage(QString("Solving maze..."));

        Algorithm* algorithm;

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

                if(step->cell() != maze->getStartCell() && step->cell() != maze->getFinishCell()) {

                    if (step->state() == State::CURRENT && lastCurrentSolve == nullptr) {
                        lastCurrentSolve = step->cell();

                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight));
                        ui->visitedCellsLabel->setText(QString("Visited cells: " + QString::number(++visitedCellCount)));
                    }
                    else if (step->state() == State::CURRENT && lastCurrentSolve != nullptr) {
                        rectItemCells[lastCurrentSolve->getX()][lastCurrentSolve->getY()]->setBackgroundColor(QColor(222, 222, 222)); // Color as visited
                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(QApplication::palette().color(QPalette::Highlight));

                        lastCurrentSolve = step->cell();

                        ui->visitedCellsLabel->setText(QString("Visited cells: " + QString::number(++visitedCellCount)));
                    }
                    else if (step->state() == State::NEIGHBOUR) {
                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(QColor(250, 128, 114));
                    }

                }
                else if (step->cell() == maze->getFinishCell()) {
                    rectItemCells[lastCurrentSolve->getX()][lastCurrentSolve->getY()]->setBackgroundColor(QColor(222, 222, 222)); // Color as visited
                }

                solvingSteps.pop();
            }
            else {
                timerTraverseMaze->stop();
                timerTraverseMaze = nullptr;
                lastCurrentSolve = nullptr;

                ui->statusbar->showMessage(QString("Finding path..."));
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

                        ui->statusbar->showMessage(QString("Maze successfully solved."));
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
