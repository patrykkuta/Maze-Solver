#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "randomizedmaze.h"
#include "customrectitem.h"
#include "breadthfirstsearch.h"
#include "depthfirstsearch.h"
#include "astarsearch.h"
#include "mazefilehandler.h"
#include "custommaze.h"
#include <QTimer>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/assets/icon128.ico"));

    ui->visitedCellColour->setPalette(colours.VISITED);
    ui->startCellColour->setPalette(colours.START);
    ui->finishCellColour->setPalette(colours.FINISH);
    ui->currentCellColour->setPalette(colours.CURRENT);
    ui->notVisitedCellColour->setPalette(colours.EMPTY);
    ui->neighbourCellColour->setPalette(colours.NEIGHBOUR);

    // Shortcuts
    ui->actionSave->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    ui->actionSave_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    ui->actionNew->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    ui->actionOpen->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    // Slots
    connect(ui->actionExit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()), Qt::QueuedConnection);
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(createNewWindow()));
    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(drawMaze()));
    connect(ui->solveButton, SIGNAL(clicked()), this, SLOT(solveMaze()));
    connect(ui->exitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()), Qt::QueuedConnection);
    connect(ui->animationSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeAnimationSpeed(int)));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));
    connect(ui->animationPlayButton, SIGNAL(clicked(bool)), this, SLOT(controlAnimationPlayback()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetMaze()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveMazeAs()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveMaze()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openMaze()));
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
        setWindowTitle(currentFileName + "* - Maze Solver"); // Indicate that the file has changed
        hasUnsavedChanges = true;

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
        maze = new RandomizedMaze(ui->columnsCount->value(), ui->rowsCount->value());

        int cellSize = qMin(ui->mazeView->width() / maze->getWidth(), ui->mazeView->height() / maze->getHeight()) - (50 / maze->getMaze().size());

        // Display not generated maze
        for (int y = 0; y < maze->getWidth(); y++) {
            rectItemCells.emplace_back();
            for (int x = 0; x < maze->getHeight(); x++) {
                Cell* current = maze->getMaze()[x][y];

                CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, colours.EMPTY, *current);
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
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.CURRENT); // Color as current
                }
                else if (step->state() == State::CURRENT && lastCurrentGenerate != nullptr) {
                    rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setCell(*lastCurrentGenerate);
                    rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setBackgroundColor(colours.EMPTY); // Color as empty

                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setCell(*step->cell());
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.CURRENT); // Color as current

                    lastCurrentGenerate = step->cell();
                }
                else if (step->state() == State::NEIGHBOUR) {
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.NEIGHBOUR); // Color as neighbour
                }

                generationSteps.erase(generationSteps.begin());

            }
            else {
                timerMazeGeneration -> stop();
                mazeCreated = true;
                generating = false;
                timerMazeGeneration = nullptr;

                rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setBackgroundColor(colours.EMPTY); // Color as visited
                rectItemCells[maze->getStartCell()->getX()][maze->getStartCell()->getY()]->setBackgroundColor(colours.START); // Color start cell
                rectItemCells[maze->getFinishCell()->getX()][maze->getFinishCell()->getY()]->setBackgroundColor(colours.FINISH); // Color finish cell

                ui->statusbar->showMessage(QString("Maze successfully generated."));

                lastCurrentGenerate = nullptr;
            }
        });

        timerMazeGeneration->start(1000 / animationSpeed);
    }
}

void MainWindow::solveMaze() {
    if (mazeCreated && !generating && !solving) {

        resetMaze();

        solving = true;

        ui->statusbar->showMessage(QString("Solving maze..."));

        PathFindingAlgorithm* algorithm;

        for (QRadioButton* rb: ui->solveMethodGroupBox->findChildren<QRadioButton*>()) {
            if(rb->isChecked()) {
                if (rb->text() == "Breadth-First Search Algorithm") {
                    algorithm = new BreadthFirstSearch();
                }
                else if (rb->text() == "Depth-First Search Algorithm") {
                    algorithm = new DepthFirstSearch();
                }
                else if (rb->text() == "A* Search") {
                    algorithm = new AStarSearch();
                }
            }
        }

        algorithm->solve(*maze);
        solvingSteps = algorithm->getSolvingSteps();
        solutionPath = algorithm->getSolution();

        timerTraverseMaze = new QTimer(this);
        timerShowPath = new QTimer(this);

        connect(timerTraverseMaze, &QTimer::timeout, [=]() {
            if (!solvingSteps.empty()) {
                Step* step = solvingSteps.front();

                if(step->cell() != maze->getStartCell() && step->cell() != maze->getFinishCell()) {

                    if (step->state() == State::CURRENT && lastCurrentSolve == nullptr) {
                        lastCurrentSolve = step->cell();

                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.CURRENT);
                        ui->visitedCellsLabel->setText(QString("Visited cells: " + QString::number(++visitedCellCount)));
                    }
                    else if (step->state() == State::CURRENT && lastCurrentSolve != nullptr) {
                        rectItemCells[lastCurrentSolve->getX()][lastCurrentSolve->getY()]->setBackgroundColor(colours.VISITED); // Color as visited
                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.CURRENT);

                        lastCurrentSolve = step->cell();
                    }
                    else if (step->state() == State::NEIGHBOUR) {
                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.NEIGHBOUR);
                    }

                }
                else if (step->cell() == maze->getFinishCell()) {
                    rectItemCells[lastCurrentSolve->getX()][lastCurrentSolve->getY()]->setBackgroundColor(colours.VISITED); // Color as visited
                }

                solvingSteps.pop();
                ui->visitedCellsLabel->setText(QString("Visited cells: " + QString::number(++visitedCellCount)));
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
                            rectItemCells[cell->getX()][cell->getY()]->setBackgroundColor(colours.CURRENT); // Color as solution
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
    if (!generating && !solving) {
        for(vector<CustomRectItem*>& row: rectItemCells) {
            for (CustomRectItem* cell: row) {
                if (*cell->getCell() != *maze->getStartCell() && *cell->getCell() != *maze->getFinishCell()) {
                    cell->setBackgroundColor(colours.EMPTY);
                }
            }
        }

        mazeCreated = true;
        generating = false;
        solving = false;
        solved = false;
        pathLength = 0;
        visitedCellCount = 0;
        ui->visitedCellsLabel->setText(QString("Visited cells: 0"));
        ui->pathLengthLabel->setText(QString("Path length: 0"));
    }
}

void MainWindow::createNewWindow() {
    QString appPath = QApplication::applicationFilePath();

    QProcess::startDetached(appPath);
    QApplication::quit();
}

void MainWindow::zoom(int value) {
    double scaleFactor;

    if (value > 0) {
        scaleFactor = 1 + value / 20.0;
    }
    else {
        scaleFactor = 1 + value / 100.0;
    }

    ui->mazeView->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
    ui->zoomLabel->setText(QString("Zoom: " + QString::number(scaleFactor) + "x"));
}

void MainWindow::controlAnimationPlayback() {
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
}

void MainWindow::changeAnimationSpeed(int value) {

    animationSpeed = value;

    ui->animationSpeedLabel->setText(QString("Speed: " + QString::number(animationSpeed) + " (steps per second)"));

    if(timerTraverseMaze != nullptr) {
        timerTraverseMaze->setInterval(1000.0 / animationSpeed);
    }

    if(timerMazeGeneration != nullptr) {
        timerMazeGeneration->setInterval(1000.0 / animationSpeed);
    }
}

bool MainWindow::saveMaze() {
    if (currentFileDir.isEmpty()) return saveMazeAs();
    else if (!mazeCreated) {
        QMessageBox::critical(this, "Error", "Cannot save an empty maze. Please create a maze first.");
        return false;
    }
    else if(!currentFileDir.isEmpty() && !currentFileDir.isNull()) {
        MazeFileHandler file(currentFileDir.toStdString());
        if (file.saveMaze(maze)) {
            ui->statusbar->showMessage(QString("Maze file successfully saved."));

            hasUnsavedChanges = false;
            setWindowTitle(QFileInfo(currentFileDir).baseName() + " - Maze Solver");

            return true;
        }
        else {
            ui->statusbar->showMessage(QString("Unable to save the maze file."));
            return false;
        }
    }

    return false;

}

bool MainWindow::saveMazeAs() {
    if (!mazeCreated) {
        QMessageBox::critical(this, "Error", "Cannot save an empty maze. Please create a maze first.");
        return false;
    }

    QString name;

    if(currentFileName == "New maze file") {
        QString currentDate = QDateTime::currentDateTime().toString("ddMMyyyyhhmmss");
        name = QString::number(maze->getWidth()) + "x" + QString::number(maze->getHeight()) + "_Maze_" + currentDate;
    }
    else {
        name = currentFileName;
    }

    currentFileDir = QFileDialog::getSaveFileName(this, "Save Maze As", name, "Maze Files (*.maze)");

    if(!currentFileDir.isEmpty() && !currentFileDir.isNull()) {
        MazeFileHandler file(currentFileDir.toStdString());
        if (file.saveMaze(maze)) {
            ui->statusbar->showMessage(QString("Maze file successfully saved."));

            hasUnsavedChanges = false;
            currentFileName = QFileInfo(currentFileDir).baseName();
            setWindowTitle(currentFileName + " - Maze Solver");

            return true;
        }
        else {
            ui->statusbar->showMessage(QString("Unable to save the maze file."));
            return false;
        }
    }
    else {
        return false;
    }

}

void MainWindow::openMaze() {

    if(!hasUnsavedChanges) {
        currentFileDir = QFileDialog::getOpenFileName(this, "Open Maze", QString(), "Maze Files (*.maze)");

        if(currentFileDir.isEmpty()) return;

        maze = new CustomMaze(currentFileDir.toStdString());
        maze->generateMaze();

        if (!maze->getMaze().empty()) {
            rectItemCells.clear();
            hasUnsavedChanges = false;

            QGraphicsScene* mazeScene = new QGraphicsScene(this);

            int cellSize = qMin(ui->mazeView->width() / maze->getWidth(), ui->mazeView->height() / maze->getHeight()) - (50 / maze->getMaze().size());

            for (int y = 0; y < maze->getWidth(); y++) {
                rectItemCells.emplace_back();
                for (int x = 0; x < maze->getHeight(); x++) {
                    Cell* current = maze->getMaze()[x][y];

                    CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, colours.EMPTY, *current);
                    rectItemCells[y].push_back(rect);

                    // Add the item to the scene
                    mazeScene->addItem(rect);
                }
            }

            mazeCreated = true;
            rectItemCells[maze->getStartCell()->getX()][maze->getStartCell()->getY()]->setBackgroundColor(colours.START);
            rectItemCells[maze->getFinishCell()->getX()][maze->getFinishCell()->getY()]->setBackgroundColor(colours.FINISH);

            ui->mazeView->setScene(mazeScene);

            ui->statusbar->showMessage(QString("Maze file successfully opened."));

            currentFileName = QFileInfo(currentFileDir).baseName();
            setWindowTitle(currentFileName + " - Maze Solver");
        }
        else {
            ui->statusbar->showMessage(QString("Unable to open the file."));
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("There are unsaved changes. Do you want to save them?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        int userChoice = msgBox.exec();

        switch (userChoice) {
        case QMessageBox::Save:
            if(saveMaze()) {
                hasUnsavedChanges = false;
                openMaze();
            }
            break;

        case QMessageBox::Discard:
            currentFileDir = QFileDialog::getOpenFileName(this, "Open Maze", QString(), "Maze Files (*.maze)");

            if(currentFileDir.isEmpty()) return;

            maze = new CustomMaze(currentFileDir.toStdString());
            maze->generateMaze();

            if (!maze->getMaze().empty()) {
                rectItemCells.clear();
                hasUnsavedChanges = false;

                QGraphicsScene* mazeScene = new QGraphicsScene(this);

                int cellSize = qMin(ui->mazeView->width() / maze->getWidth(), ui->mazeView->height() / maze->getHeight()) - (50 / maze->getMaze().size());

                for (int y = 0; y < maze->getWidth(); y++) {
                    rectItemCells.emplace_back();
                    for (int x = 0; x < maze->getHeight(); x++) {
                        Cell* current = maze->getMaze()[x][y];

                        CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, colours.EMPTY, *current);
                        rectItemCells[y].push_back(rect);

                        // Add the item to the scene
                        mazeScene->addItem(rect);
                    }
                }

                mazeCreated = true;
                rectItemCells[maze->getStartCell()->getX()][maze->getStartCell()->getY()]->setBackgroundColor(colours.START);
                rectItemCells[maze->getFinishCell()->getX()][maze->getFinishCell()->getY()]->setBackgroundColor(colours.FINISH);

                ui->mazeView->setScene(mazeScene);

                ui->statusbar->showMessage(QString("Maze file successfully opened."));

                currentFileName = QFileInfo(currentFileDir).baseName();
                setWindowTitle(currentFileName + " - Maze Solver");
            }
            else {
                ui->statusbar->showMessage(QString("Unable to open the file."));
            }

            break;

        case QMessageBox::Cancel:
            break;
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(hasUnsavedChanges) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("There are unsaved changes. Do you want to save them?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        int userChoice = msgBox.exec();

        switch (userChoice) {
        case QMessageBox::Save:
            if(saveMazeAs()) event->accept();
            break;

        case QMessageBox::Discard:
            event->accept();
            break;

        case QMessageBox::Cancel:
            event->ignore();
            break;
        }
    }
    else {
        event->accept();
    }
}
