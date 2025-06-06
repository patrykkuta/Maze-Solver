#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QResizeEvent>
#include "pathfindingalgorithm.h"
#include "qapplication.h"
#include "randomizedprimsalgorithm.h"
#include "customrectitem.h"
#include <QTimer>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The MainWindow class represents the main application window for a maze-solving program.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow object.
     * @param parent The parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot function to draw the maze.
     */
    void drawMaze();

    /**
     * @brief Slot function to solve the maze.
     */
    void solveMaze();

    /**
     * @brief Slot function to create a new window.
     */
    void createNewWindow();

    /**
     * @brief Slot function to zoom in or out.
     * @param value The zoom level.
     */
    void zoom(int value);

    /**
     * @brief Slot function to control animation playback.
     */
    void controlAnimationPlayback();

    /**
     * @brief Slot function to change the animation speed.
     * @param value The speed value.
     */
    void changeAnimationSpeed(int value);

    /**
     * @brief Slot function to reset the maze solution.
     */
    void resetMaze();

    /**
     * @brief Slot function to save the maze.
     * @return True if successful, false otherwise.
     */
    bool saveMaze();

    /**
     * @brief Slot function to save the maze with a new filename.
     * @return True if successful, false otherwise.
     */
    bool saveMazeAs();

    /**
     * @brief Slot function to open an existing maze.
     */
    void openMaze();

private:
    /**
     * @brief Struct containing colors used in the maze visualization.
     */
    struct {
        const QColor VISITED = QColor(222, 222, 222);    /**< Color for visited cells. */
        const QColor START = QColor(144, 238, 144);      /**< Color for the start cell. */
        const QColor FINISH = QColor(255, 0, 0);     /**< Color for the finish cell. */
        const QColor CURRENT = QApplication::palette().color(QPalette::Highlight);    /**< Color for the current cell. */
        const QColor EMPTY = QApplication::palette().color(QPalette::Base);      /**< Color for empty cells. */
        const QColor NEIGHBOUR = QColor(250, 128, 114);  /**< Color for neighbouring cells. */
    } colours;

    Ui::MainWindow *ui;  /**< User interface for the main window. */
    Maze *maze;          /**< A pointer to a Maze object. */
    bool mazeCreated;    /**< Flag indicating if a maze has been created. */
    vector<vector<CustomRectItem*>> rectItemCells;  /**< 2D vector of CustomRectItem pointers representing cells in the maze. */
    bool solving;        /**< Flag indicating if maze solving is in progress. */
    bool solved;         /**< Flag indicating if the maze has been successfully solved. */
    bool generating;     /**< Flag indicating if maze generation is in progress. */
    int animationSpeed;  /**< Speed of the maze animation. */
    QTimer *timerTraverseMaze;    /**< Timer for maze traversal animation. */
    QTimer *timerShowPath;        /**< Timer for displaying the solution path animation. */
    QTimer *timerMazeGeneration;  /**< Timer for maze generation animation. */
    vector<Step>* solvingSteps;    /**< Queue of steps for maze solving. */
    vector<Step>* generationSteps; /**< Vector of steps for maze generation. */
    vector<Cell*> solutionPath;   /**< Vector representing the solution path. */
    Cell *lastCurrentSolve;       /**< Pointer to the last current cell during maze solving. */
    Cell *lastCurrentGenerate;    /**< Pointer to the last current cell during maze generation. */
    int visitedCellCount;         /**< Count of visited cells during maze solving. */
    int pathLength;               /**< Length of the solution path. */
    bool hasUnsavedChanges;       /**< Flag indicating if there are unsaved changes to the maze. */
    QString currentFileName;      /**< Current filename of the maze file. */
    QString currentFileDir;       /**< Directory of the current maze file. */
    bool shouldQuit;              /**< Flag indicating whether the application should quit. */

    /**
     * @brief promptForSave Displays a QMessageBox prompting user to Save or Discard changes, or Cancel the exiting process.
     * @return Integer value corresponding to user choice
     */
    int promptForSave();

    /**
     * @brief Overridden closeEvent function to handle the closing of the main window.
     * @param event The close event.
     */
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
