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

    // Set color palettes for UI elements
    ui->visitedCellColour->setPalette(colours.VISITED);
    ui->startCellColour->setPalette(colours.START);
    ui->finishCellColour->setPalette(colours.FINISH);
    ui->currentCellColour->setPalette(colours.CURRENT);
    ui->notVisitedCellColour->setPalette(colours.EMPTY);
    ui->neighbourCellColour->setPalette(colours.NEIGHBOUR);

    // Set shortcuts for actions
    ui->actionSave->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    ui->actionSave_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    ui->actionNew->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    ui->actionOpen->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    // Connect slots for UI actions
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

    // Initialize member variables
    maze = nullptr;
    mazeCreated = false;
    solving = false;
    solved = false;
    generating = false;
    animationSpeed = 100;
    timerTraverseMaze = nullptr;
    timerShowPath = nullptr;
    timerMazeGeneration = nullptr;
    lastCurrentSolve = nullptr;
    lastCurrentGenerate = nullptr;
    visitedCellCount = 0;
    pathLength = 0;
    hasUnsavedChanges = false;
    currentFileName = "New maze file";
    currentFileDir = "";
    shouldQuit = false;
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
    // Check if the application is not currently solving or generating a maze
    if (!solving && !generating) {
        // Indicate that the file has changed and there are unsaved changes
        setWindowTitle(currentFileName + "* - Maze Solver");
        hasUnsavedChanges = true;

        // Clean up existing maze and scene
        if (maze != nullptr) {
            delete maze;
        }

        if (ui->mazeView->scene() != nullptr) {
            delete ui->mazeView->scene();
        }

        // Display status message
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

        // Create a new QGraphicsScene to display the maze
        QGraphicsScene* mazeScene = new QGraphicsScene(this);

        // Create a new RandomizedMaze with specified dimensions and algorithm
        maze = new RandomizedMaze(ui->columnsCount->value(), ui->rowsCount->value(), new RandomizedPrimsAlgorithm(ui->columnsCount->value(), ui->rowsCount->value()));

        // Calculate the size of each maze cell
        int cellSize = qMin(ui->mazeView->width() / maze->getWidth(), ui->mazeView->height() / maze->getHeight()) - (50 / maze->getMaze().size());

        // Display not generated maze
        for (int y = 0; y < maze->getWidth(); y++) {
            rectItemCells.emplace_back();
            for (int x = 0; x < maze->getHeight(); x++) {
                Cell* current = maze->getMaze()[x][y];

                // Create a CustomRectItem representing the maze cell
                CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, colours.EMPTY, *current);
                rectItemCells[y].push_back(rect);

                // Add the item to the scene
                mazeScene->addItem(rect);
            }
        }

        // Set the QGraphicsScene for the maze view
        ui->mazeView->setScene(mazeScene);

        // Generate maze
        maze->generateMaze();

        // Get the maze generation steps
        generationSteps = maze->getGeneratingAlgorithm()->getGenerationSteps();

        // Create a timer for animating the maze generation process
        timerMazeGeneration = new QTimer(this);

        // Connect the timer to the timeout signal
        connect(timerMazeGeneration, &QTimer::timeout, [=]() {
            // Check if there are still generation steps
            if (!generationSteps.empty()) {
                Step* step = &generationSteps.at(0);

                // Handle different states of the generation step
                if (step->state() == State::CURRENT && lastCurrentGenerate == nullptr) {
                    // Set the current cell and color it as current
                    lastCurrentGenerate = step->cell();
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setCell(*step->cell());
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.CURRENT);
                }
                else if (step->state() == State::CURRENT && lastCurrentGenerate != nullptr) {
                    // Reset the color of the last current cell and update the new current cell
                    rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setCell(*lastCurrentGenerate);
                    rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setBackgroundColor(colours.EMPTY);

                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setCell(*step->cell());
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.CURRENT);

                    lastCurrentGenerate = step->cell();
                }
                else if (step->state() == State::NEIGHBOUR) {
                    // Color the cell as a neighbour
                    rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.NEIGHBOUR);
                }

                // Remove the processed step from the vector
                generationSteps.erase(generationSteps.begin());
            }
            else {
                // Maze generation completed
                timerMazeGeneration->stop();
                mazeCreated = true;
                generating = false;
                timerMazeGeneration = nullptr;

                // Reset the color of the last current cell and color start and finish cells
                rectItemCells[lastCurrentGenerate->getX()][lastCurrentGenerate->getY()]->setBackgroundColor(colours.EMPTY);
                rectItemCells[maze->getStartCell()->getX()][maze->getStartCell()->getY()]->setBackgroundColor(colours.START);
                rectItemCells[maze->getFinishCell()->getX()][maze->getFinishCell()->getY()]->setBackgroundColor(colours.FINISH);

                // Display success message
                ui->statusbar->showMessage(QString("Maze successfully generated."));

                lastCurrentGenerate = nullptr;
            }
        });

        // Start the timer with the specified animation speed
        timerMazeGeneration->start(1000 / animationSpeed);
    }
}

void MainWindow::solveMaze() {
    // Check if a maze is created, not currently generating or solving
    if (mazeCreated && !generating && !solving) {
        // Reset maze solving visualization
        resetMaze();

        // Set solving flag
        solving = true;

        // Display solving status in the status bar
        ui->statusbar->showMessage(QString("Solving maze..."));

        // Initialize a pointer to a pathfinding algorithm
        PathFindingAlgorithm* algorithm = nullptr;

        // Iterate through radio buttons to find what algorithm was selected
        for (QRadioButton* rb: ui->solveMethodGroupBox->findChildren<QRadioButton*>()) {
            if(rb->isChecked()) {
                // Create the corresponding pathfinding algorithm based on the selected radio button
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

        // Solve the maze using the selected algorithm
        algorithm->solve(*maze);
        solvingSteps = algorithm->getSolvingSteps();
        solutionPath = algorithm->getSolution();

        // Create timers for animating the solving process and displaying the final path
        timerTraverseMaze = new QTimer(this);
        timerShowPath = new QTimer(this);

        // Connect the timeout signal of the traverse maze timer
        connect(timerTraverseMaze, &QTimer::timeout, [=]() {
            if (!solvingSteps.empty()) {
                // Process the next solving step
                Step* step = solvingSteps.front();

                if (step->cell() != maze->getStartCell() && step->cell() != maze->getFinishCell()) {
                    if (step->state() == State::CURRENT && lastCurrentSolve == nullptr) {
                        // Colour the current solving step
                        lastCurrentSolve = step->cell();
                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.CURRENT);
                    }
                    else if (step->state() == State::CURRENT && lastCurrentSolve != nullptr) {
                        // Colour the last current step as visited and current step as current
                        rectItemCells[lastCurrentSolve->getX()][lastCurrentSolve->getY()]->setBackgroundColor(colours.VISITED);
                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.CURRENT);
                        lastCurrentSolve = step->cell();
                    }
                    else if (step->state() == State::NEIGHBOUR) {
                        // Colour as neighbour
                        rectItemCells[step->cell()->getX()][step->cell()->getY()]->setBackgroundColor(colours.NEIGHBOUR);
                    }
                }

                // Remove the processed step from the queue
                solvingSteps.pop();

                // Update visited cell count if the step is a current state
                if (step->state() == State::CURRENT) {
                    ui->visitedCellsLabel->setText(QString("Visited cells: " + QString::number(++visitedCellCount)));
                }
            }
            else {
                // Maze traversal completed, stop the timer
                timerTraverseMaze->stop();
                timerTraverseMaze = nullptr;
                lastCurrentSolve = nullptr;

                // Update status message and connect the timeout signal of the show path timer
                ui->statusbar->showMessage(QString("Finding path..."));
                connect(timerShowPath, &QTimer::timeout, [=]() {
                    if (!solutionPath.empty()) {
                        // Display the solution path step by step
                        Cell* cell = solutionPath.at(0);

                        if (cell != maze->getStartCell() && cell != maze->getFinishCell()) {
                            rectItemCells[cell->getX()][cell->getY()]->setBackgroundColor(colours.CURRENT);
                            rectItemCells[cell->getX()][cell->getY()]->update();
                        }

                        // Update path length label and remove the processed cell from the solution path
                        ui->pathLengthLabel->setText(QString("Path length: " + QString::number(++pathLength)));
                        solutionPath.erase(solutionPath.begin());
                    }
                    else {
                        // Solution path display completed, stop the timer
                        timerShowPath->stop();
                        timerShowPath = nullptr;

                        // Reset solving flags and display success message
                        solving = false;
                        solved = true;
                        ui->statusbar->showMessage(QString("Maze successfully solved."));
                    }
                });

                // Start the show path timer with appropriate interval
                timerShowPath->start(500 / solutionPath.size());
            }
        });

        // Start the traverse maze timer with the specified animation speed
        timerTraverseMaze->start(1000 / animationSpeed);

        // Delete the allocated algorithm object to avoid memory leaks
        delete algorithm;
    }
}

void MainWindow::resetMaze() {
    // Check if the application is not currently generating or solving
    if (!generating && !solving && solved) {
        // Iterate through the maze cells and reset visual markings
        for (vector<CustomRectItem*>& row : rectItemCells) {
            for (CustomRectItem* cell : row) {
                // Check if the cell is not the start or finish cell
                if (*cell->getCell() != *maze->getStartCell() && *cell->getCell() != *maze->getFinishCell()) {
                    // Reset the background color to empty
                    cell->setBackgroundColor(colours.EMPTY);
                }
            }
        }

        // Reset flags and statistics
        mazeCreated = true;
        generating = false;
        solving = false;
        solved = false;
        pathLength = 0;
        visitedCellCount = 0;

        // Update UI labels for visited cells and path length
        ui->visitedCellsLabel->setText(QString("Visited cells: 0"));
        ui->pathLengthLabel->setText(QString("Path length: 0"));
    }
}

void MainWindow::createNewWindow() {
    // Quit the current application instance
    QApplication::quit();

    // Check if a new instance should be created
    if (shouldQuit) {
        // Get the application filepath
        QString appPath = QApplication::applicationFilePath();

        // Create a new window
        QProcess::startDetached(appPath);
    }
}

void MainWindow::zoom(int value) {
    double scaleFactor;

    // Determine the scale factor based on the provided zoom value
    if (value > 0) {
        scaleFactor = 1 + value / 20.0;
    }
    else {
        scaleFactor = 1 + value / 100.0;
    }

    // Set the transform of the maze view to apply the zoom
    ui->mazeView->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));

    // Update the UI label with the current zoom factor
    ui->zoomLabel->setText(QString("Zoom: " + QString::number(scaleFactor) + "x"));
}

void MainWindow::controlAnimationPlayback() {
    // Check if the traverse maze timer is active
    if (timerTraverseMaze != nullptr) {
        if (timerTraverseMaze->isActive()) {
            // Pause the solving animation
            ui->statusbar->showMessage(QString("Solving paused."));
            ui->animationPlayButton->setText(QString("Resume"));
            timerTraverseMaze->stop();
        }
        else {
            // Resume the solving animation
            ui->statusbar->showMessage(QString("Solving maze..."));
            ui->animationPlayButton->setText(QString("Pause"));
            timerTraverseMaze->start();
        }
    }
    // Check if the maze generation timer is active
    else if (timerMazeGeneration != nullptr) {
        if (timerMazeGeneration->isActive()) {
            // Pause the maze generation animation
            ui->statusbar->showMessage(QString("Generating paused."));
            ui->animationPlayButton->setText(QString("Resume"));
            timerMazeGeneration->stop();
        }
        else {
            // Resume the maze generation animation
            ui->statusbar->showMessage(QString("Generating maze..."));
            ui->animationPlayButton->setText(QString("Pause"));
            timerMazeGeneration->start();
        }
    }
    // Check if the show path timer is active
    else if (timerShowPath != nullptr) {
        if (timerShowPath->isActive()) {
            // Pause the pathfinding animation
            ui->statusbar->showMessage(QString("Finding paused."));
            ui->animationPlayButton->setText(QString("Resume"));
            timerShowPath->stop();
        }
        else {
            // Resume the pathfinding animation
            ui->statusbar->showMessage(QString("Finding path..."));
            ui->animationPlayButton->setText(QString("Pause"));
            timerShowPath->start();
        }
    }
}

void MainWindow::changeAnimationSpeed(int value) {
    // Update the animation speed value
    animationSpeed = value;

    // Update the UI label with the current animation speed
    ui->animationSpeedLabel->setText(QString("Speed: " + QString::number(animationSpeed) + " (steps per second)"));

    // Check if the traverse maze timer is active and adjust its interval
    if (timerTraverseMaze != nullptr) {
        timerTraverseMaze->setInterval(1000.0 / animationSpeed);
    }

    // Check if the maze generation timer is active and adjust its interval
    if (timerMazeGeneration != nullptr) {
        timerMazeGeneration->setInterval(1000.0 / animationSpeed);
    }
}

bool MainWindow::saveMaze() {
    // Check if the file was saved before, if not invoke save as function
    if (currentFileDir.isEmpty()) {
        return saveMazeAs();
    }
    // Check if the maze has not been created and display an error message
    else if (!mazeCreated) {
        QMessageBox::critical(this, "Error", "Cannot save an empty maze. Please create a maze first.");
        return false;
    }
    // Check if the current file directory is not empty and not null
    else if (!currentFileDir.isEmpty() && !currentFileDir.isNull()) {
        // Create a MazeFileHandler object for saving the maze
        MazeFileHandler file(currentFileDir.toStdString());

        // Save the maze to the file
        if (file.saveMaze(maze)) {
            // Update status bar and window title
            ui->statusbar->showMessage(QString("Maze file successfully saved."));
            hasUnsavedChanges = false;
            setWindowTitle(QFileInfo(currentFileDir).baseName() + " - Maze Solver");

            return true;
        }
        else {
            // Display error message if saving fails
            ui->statusbar->showMessage(QString("Unable to save the maze file."));
            return false;
        }
    }

    return false;
}

bool MainWindow::saveMazeAs() {
    // Check if the maze has not been created and display an error message
    if (!mazeCreated) {
        QMessageBox::critical(this, "Error", "Cannot save an empty maze. Please create a maze first.");
        return false;
    }

    QString name;

    // If the file name is a default name, create a new name based on the maze size and current timestamp
    if (currentFileName == "New maze file") {
        QString currentDate = QDateTime::currentDateTime().toString("ddMMyyyyhhmmss");
        name = QString::number(maze->getWidth()) + "x" + QString::number(maze->getHeight()) + "_Maze_" + currentDate;
    }
    else {
        name = currentFileName;
    }

    // Prompt the user to choose a file path and file name using a file dialog
    currentFileDir = QFileDialog::getSaveFileName(this, "Save Maze As", name, "Maze Files (*.maze)");

    // Check if the user canceled the operation
    if (!currentFileDir.isEmpty() && !currentFileDir.isNull()) {
        // Create a MazeFileHandler object for saving the maze
        MazeFileHandler file(currentFileDir.toStdString());

        // Save the maze to the file
        if (file.saveMaze(maze)) {
            // Update status bar, current file name, and window title
            ui->statusbar->showMessage(QString("Maze file successfully saved."));
            hasUnsavedChanges = false;
            currentFileName = QFileInfo(currentFileDir).baseName();
            setWindowTitle(currentFileName + " - Maze Solver");

            return true;
        }
        else {
            // Display error message if saving fails
            ui->statusbar->showMessage(QString("Unable to save the maze file."));
            return false;
        }
    }
    else {
        return false;
    }
}

void MainWindow::openMaze() {
    // Check if there are no unsaved changes
    if (!hasUnsavedChanges) {
        // Prompt the user to choose a maze file using a file dialog
        currentFileDir = QFileDialog::getOpenFileName(this, "Open Maze", QString(), "Maze Files (*.maze)");

        // Check if the user canceled the operation
        if (currentFileDir.isEmpty()) return;

        // Create a CustomMaze object and generate the maze
        maze = new CustomMaze(currentFileDir.toStdString());
        maze->generateMaze();

        // Check if the maze is not empty
        if (!maze->getMaze().empty()) {
            rectItemCells.clear();
            hasUnsavedChanges = false;

            QGraphicsScene* mazeScene = new QGraphicsScene(this);

            int cellSize = qMin(ui->mazeView->width() / maze->getWidth(), ui->mazeView->height() / maze->getHeight()) - (50 / maze->getMaze().size());

            // Display the maze on the UI
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
            // Display error message if unable to open the file
            ui->statusbar->showMessage(QString("Unable to open the file."));
        }
    }
    // Check if there are unsaved changes
    else {
        // Prompt the user to save unsaved changes
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("There are unsaved changes. Do you want to save them?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        // Get user's choice
        int userChoice = msgBox.exec();

        switch (userChoice) {
        case QMessageBox::Save:
            // Save the maze if the user chooses to save
            if (saveMaze()) {
                hasUnsavedChanges = false;
                openMaze();
            }
            break;

        case QMessageBox::Discard:
            // Discard changes and proceed to open a new maze
            currentFileDir = QFileDialog::getOpenFileName(this, "Open Maze", QString(), "Maze Files (*.maze)");

            if (currentFileDir.isEmpty()) return;

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
            // Cancel the operation if the user chooses to cancel
            break;
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // Check if there are unsaved changes
    if (hasUnsavedChanges) {
        // Prompt the user to save unsaved changes
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("There are unsaved changes. Do you want to save them?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        // Get user's choice
        int userChoice = msgBox.exec();

        switch (userChoice) {
        case QMessageBox::Save:
            // Save the maze if the user chooses to save, allow the window to close
            if (saveMazeAs()) {
                shouldQuit = true;
                event->accept();
            }
            break;

        case QMessageBox::Discard:
            // Discard changes and allow the window to close
            shouldQuit = true;
            event->accept();
            break;

        case QMessageBox::Cancel:
            // Cancel the close operation if the user chooses to cancel, do not allow the window to close
            event->ignore();
            break;
        }
    }
    // No unsaved changes, allow the window to close
    else {
        shouldQuit = true;
        event->accept();
    }
}
