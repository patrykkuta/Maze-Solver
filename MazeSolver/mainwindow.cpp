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

        if(timer != nullptr) {
            timer->setInterval(1000 / animationSpeed);
        }
    });

    animationSpeed = ui->animationSpeedSlider->value();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui->mazeView->scene();
    delete maze;
    delete ui;
}

void MainWindow::createMaze() {
    if (maze != nullptr) {
        delete maze;
    }

    if (ui->mazeView->scene()) {
        delete ui->mazeView->scene();
    }

    rectItemCells.clear();
    solving = false;

    QGraphicsScene* mazeScene = new QGraphicsScene(this);

    maze = new RandomizedMaze(ui->rowsCount->value(), ui->columnsCount->value());

    int cellSize = qMin(ui->mazeView->width() / maze->getWidth(), ui->mazeView->height() / maze->getHeight()) - 5/maze->getMaze().size();

    for (int y = 0; y < maze->getWidth(); y++) {
        rectItemCells.emplace_back();
        for (int x = 0; x < maze->getHeight(); x++) {
            Cell* current = maze->getMaze()[x][y];
            QColor color(255, 255, 255);

            if (*current == *maze->getStartCell()) color.setRgb(144,238,144);
            else if (*current == *maze->getFinishCell()) color.setRgb(250,128,114);

            QString textInfo = QString("(%1, %2)").arg(y).arg(x);
            CustomRectItem *rect = new CustomRectItem(y * cellSize, x * cellSize, cellSize, cellSize, color, *current, textInfo);
            rectItemCells[y].push_back(rect);

            // Add the item to the scene
            mazeScene->addItem(rect);
        }
    }

    ui->mazeView->setScene(mazeScene);
    mazeCreated = true;
}

void MainWindow::solveMaze() {
    if (mazeCreated && !solving) {

        solving = true;

        Algorithm* algorithm = nullptr;

        for (QRadioButton* rb: ui->solveMethodGroupBox->findChildren<QRadioButton*>()) {
            if(rb->isChecked()) {
                if (rb->text() == "Breadth-First Search Algorithm") {
                    algorithm = new BreadthFirstSearch();
                }
                // else if(rb->text() == "Depth-First Search Algorithm") {
                //     algorithm = new DepthFirstSearch();
                // }
            }
        }

        steps = algorithm->solve(*maze);

        timer = new QTimer(this);

        connect(timer, &QTimer::timeout, [=]() {
            if (!steps.empty()) {
                Cell* cell = steps.back();

                rectItemCells[cell->getX()][cell->getY()]->setColor(QColor(222, 222, 222));
                rectItemCells[cell->getX()][cell->getY()]->update();

                steps.pop_back();
            }
            else {
                timer->stop();

                timer = nullptr;
            }
        });

        timer->start(1000 / animationSpeed);

        delete algorithm;
    }
}
