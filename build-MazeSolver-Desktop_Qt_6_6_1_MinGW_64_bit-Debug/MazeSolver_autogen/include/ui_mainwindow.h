/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionOpen;
    QAction *actionNew;
    QAction *actionExit;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_7;
    QGraphicsView *mazeView;
    QLabel *zoomLabel;
    QSlider *zoomSlider;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *mazeParametersGroupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *rowsCount;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *columnsCount;
    QPushButton *generateButton;
    QGroupBox *solveMethodGroupBox;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *bfsRButton;
    QRadioButton *dfsRButton;
    QRadioButton *aStarRButton;
    QPushButton *solveButton;
    QGroupBox *animationGroupBox;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *animationSpeedLabel;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSlider *animationSpeedSlider;
    QLabel *animationSpeedMaxLabel;
    QPushButton *animationPlayButton;
    QHBoxLayout *horizontalLayout_7;
    QLabel *visitedCellsLabel;
    QLabel *pathLengthLabel;
    QSpacerItem *verticalSpacer;
    QGroupBox *colorLegendGroupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_8;
    QWidget *notVisitedCellColour;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_9;
    QWidget *finishCellColour;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout;
    QWidget *neighbourCellColour;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_10;
    QWidget *startCellColour;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_4;
    QWidget *visitedCellColour;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_11;
    QWidget *currentCellColour;
    QLabel *label_6;
    QPushButton *resetButton;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1000, 750);
        MainWindow->setMinimumSize(QSize(1000, 750));
        QIcon icon;
        icon.addFile(QString::fromUtf8("assets/icon128.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName("actionSave_as");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionExit->setMenuRole(QAction::QuitRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, 10, 10, 10);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        mazeView = new QGraphicsView(centralwidget);
        mazeView->setObjectName("mazeView");
        sizePolicy.setHeightForWidth(mazeView->sizePolicy().hasHeightForWidth());
        mazeView->setSizePolicy(sizePolicy);
        mazeView->setMinimumSize(QSize(0, 0));
        mazeView->setFrameShape(QFrame::StyledPanel);
        mazeView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        mazeView->setDragMode(QGraphicsView::ScrollHandDrag);
        mazeView->setResizeAnchor(QGraphicsView::NoAnchor);

        verticalLayout_7->addWidget(mazeView);

        zoomLabel = new QLabel(centralwidget);
        zoomLabel->setObjectName("zoomLabel");
        zoomLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(zoomLabel);

        zoomSlider = new QSlider(centralwidget);
        zoomSlider->setObjectName("zoomSlider");
        zoomSlider->setMinimum(-100);
        zoomSlider->setMaximum(100);
        zoomSlider->setSingleStep(1);
        zoomSlider->setSliderPosition(0);
        zoomSlider->setTracking(true);
        zoomSlider->setOrientation(Qt::Horizontal);
        zoomSlider->setInvertedAppearance(false);
        zoomSlider->setInvertedControls(false);
        zoomSlider->setTickPosition(QSlider::TicksAbove);
        zoomSlider->setTickInterval(100);

        verticalLayout_7->addWidget(zoomSlider);


        horizontalLayout_2->addLayout(verticalLayout_7);

        verticalWidget = new QWidget(centralwidget);
        verticalWidget->setObjectName("verticalWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(verticalWidget->sizePolicy().hasHeightForWidth());
        verticalWidget->setSizePolicy(sizePolicy1);
        verticalWidget->setMinimumSize(QSize(280, 0));
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 0, 5, 0);
        mazeParametersGroupBox = new QGroupBox(verticalWidget);
        mazeParametersGroupBox->setObjectName("mazeParametersGroupBox");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mazeParametersGroupBox->sizePolicy().hasHeightForWidth());
        mazeParametersGroupBox->setSizePolicy(sizePolicy2);
        QFont font;
        font.setBold(false);
        mazeParametersGroupBox->setFont(font);
        mazeParametersGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        mazeParametersGroupBox->setFlat(false);
        verticalLayout_2 = new QVBoxLayout(mazeParametersGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(mazeParametersGroupBox);
        label->setObjectName("label");
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(label);

        rowsCount = new QSpinBox(mazeParametersGroupBox);
        rowsCount->setObjectName("rowsCount");
        rowsCount->setWrapping(false);
        rowsCount->setFrame(true);
        rowsCount->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        rowsCount->setMinimum(3);
        rowsCount->setMaximum(60);
        rowsCount->setStepType(QAbstractSpinBox::DefaultStepType);
        rowsCount->setValue(15);

        horizontalLayout_5->addWidget(rowsCount);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(mazeParametersGroupBox);
        label_2->setObjectName("label_2");
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(label_2);

        columnsCount = new QSpinBox(mazeParametersGroupBox);
        columnsCount->setObjectName("columnsCount");
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(columnsCount->sizePolicy().hasHeightForWidth());
        columnsCount->setSizePolicy(sizePolicy4);
        columnsCount->setWrapping(false);
        columnsCount->setFrame(true);
        columnsCount->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        columnsCount->setMinimum(3);
        columnsCount->setMaximum(60);
        columnsCount->setStepType(QAbstractSpinBox::DefaultStepType);
        columnsCount->setValue(15);

        horizontalLayout_3->addWidget(columnsCount);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(mazeParametersGroupBox);

        generateButton = new QPushButton(verticalWidget);
        generateButton->setObjectName("generateButton");

        verticalLayout->addWidget(generateButton);

        solveMethodGroupBox = new QGroupBox(verticalWidget);
        solveMethodGroupBox->setObjectName("solveMethodGroupBox");
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(solveMethodGroupBox->sizePolicy().hasHeightForWidth());
        solveMethodGroupBox->setSizePolicy(sizePolicy5);
        verticalLayout_3 = new QVBoxLayout(solveMethodGroupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        bfsRButton = new QRadioButton(solveMethodGroupBox);
        bfsRButton->setObjectName("bfsRButton");
        bfsRButton->setChecked(true);

        verticalLayout_3->addWidget(bfsRButton);

        dfsRButton = new QRadioButton(solveMethodGroupBox);
        dfsRButton->setObjectName("dfsRButton");

        verticalLayout_3->addWidget(dfsRButton);

        aStarRButton = new QRadioButton(solveMethodGroupBox);
        aStarRButton->setObjectName("aStarRButton");

        verticalLayout_3->addWidget(aStarRButton);


        verticalLayout->addWidget(solveMethodGroupBox);

        solveButton = new QPushButton(verticalWidget);
        solveButton->setObjectName("solveButton");

        verticalLayout->addWidget(solveButton);

        animationGroupBox = new QGroupBox(verticalWidget);
        animationGroupBox->setObjectName("animationGroupBox");
        verticalLayout_4 = new QVBoxLayout(animationGroupBox);
        verticalLayout_4->setSpacing(40);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName("verticalLayout_5");
        animationSpeedLabel = new QLabel(animationGroupBox);
        animationSpeedLabel->setObjectName("animationSpeedLabel");
        sizePolicy2.setHeightForWidth(animationSpeedLabel->sizePolicy().hasHeightForWidth());
        animationSpeedLabel->setSizePolicy(sizePolicy2);
        animationSpeedLabel->setAlignment(Qt::AlignCenter);
        animationSpeedLabel->setMargin(7);

        verticalLayout_5->addWidget(animationSpeedLabel);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(5, -1, 10, -1);
        label_4 = new QLabel(animationGroupBox);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        animationSpeedSlider = new QSlider(animationGroupBox);
        animationSpeedSlider->setObjectName("animationSpeedSlider");
        animationSpeedSlider->setMinimum(1);
        animationSpeedSlider->setMaximum(700);
        animationSpeedSlider->setValue(100);
        animationSpeedSlider->setTracking(true);
        animationSpeedSlider->setOrientation(Qt::Horizontal);
        animationSpeedSlider->setInvertedAppearance(false);
        animationSpeedSlider->setInvertedControls(false);
        animationSpeedSlider->setTickPosition(QSlider::NoTicks);
        animationSpeedSlider->setTickInterval(1);

        horizontalLayout_6->addWidget(animationSpeedSlider);

        animationSpeedMaxLabel = new QLabel(animationGroupBox);
        animationSpeedMaxLabel->setObjectName("animationSpeedMaxLabel");

        horizontalLayout_6->addWidget(animationSpeedMaxLabel);


        verticalLayout_5->addLayout(horizontalLayout_6);

        animationPlayButton = new QPushButton(animationGroupBox);
        animationPlayButton->setObjectName("animationPlayButton");
        animationPlayButton->setFlat(false);

        verticalLayout_5->addWidget(animationPlayButton);


        verticalLayout_4->addLayout(verticalLayout_5);


        verticalLayout->addWidget(animationGroupBox);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        visitedCellsLabel = new QLabel(verticalWidget);
        visitedCellsLabel->setObjectName("visitedCellsLabel");
        sizePolicy2.setHeightForWidth(visitedCellsLabel->sizePolicy().hasHeightForWidth());
        visitedCellsLabel->setSizePolicy(sizePolicy2);
        visitedCellsLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(visitedCellsLabel);

        pathLengthLabel = new QLabel(verticalWidget);
        pathLengthLabel->setObjectName("pathLengthLabel");
        sizePolicy2.setHeightForWidth(pathLengthLabel->sizePolicy().hasHeightForWidth());
        pathLengthLabel->setSizePolicy(sizePolicy2);
        pathLengthLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(pathLengthLabel);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        colorLegendGroupBox = new QGroupBox(verticalWidget);
        colorLegendGroupBox->setObjectName("colorLegendGroupBox");
        gridLayout = new QGridLayout(colorLegendGroupBox);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        notVisitedCellColour = new QWidget(colorLegendGroupBox);
        notVisitedCellColour->setObjectName("notVisitedCellColour");
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(notVisitedCellColour->sizePolicy().hasHeightForWidth());
        notVisitedCellColour->setSizePolicy(sizePolicy6);
        notVisitedCellColour->setMinimumSize(QSize(20, 20));
        notVisitedCellColour->setMaximumSize(QSize(20, 20));
        notVisitedCellColour->setAutoFillBackground(true);

        horizontalLayout_8->addWidget(notVisitedCellColour);

        label_9 = new QLabel(colorLegendGroupBox);
        label_9->setObjectName("label_9");

        horizontalLayout_8->addWidget(label_9);


        gridLayout->addLayout(horizontalLayout_8, 2, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        finishCellColour = new QWidget(colorLegendGroupBox);
        finishCellColour->setObjectName("finishCellColour");
        sizePolicy6.setHeightForWidth(finishCellColour->sizePolicy().hasHeightForWidth());
        finishCellColour->setSizePolicy(sizePolicy6);
        finishCellColour->setMinimumSize(QSize(20, 20));
        finishCellColour->setMaximumSize(QSize(20, 20));
        finishCellColour->setAutoFillBackground(true);

        horizontalLayout_9->addWidget(finishCellColour);

        label_8 = new QLabel(colorLegendGroupBox);
        label_8->setObjectName("label_8");

        horizontalLayout_9->addWidget(label_8);


        gridLayout->addLayout(horizontalLayout_9, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        neighbourCellColour = new QWidget(colorLegendGroupBox);
        neighbourCellColour->setObjectName("neighbourCellColour");
        sizePolicy6.setHeightForWidth(neighbourCellColour->sizePolicy().hasHeightForWidth());
        neighbourCellColour->setSizePolicy(sizePolicy6);
        neighbourCellColour->setMinimumSize(QSize(20, 20));
        neighbourCellColour->setMaximumSize(QSize(20, 20));
        neighbourCellColour->setAutoFillBackground(true);

        horizontalLayout->addWidget(neighbourCellColour);

        label_3 = new QLabel(colorLegendGroupBox);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        startCellColour = new QWidget(colorLegendGroupBox);
        startCellColour->setObjectName("startCellColour");
        sizePolicy6.setHeightForWidth(startCellColour->sizePolicy().hasHeightForWidth());
        startCellColour->setSizePolicy(sizePolicy6);
        startCellColour->setMinimumSize(QSize(20, 20));
        startCellColour->setMaximumSize(QSize(20, 20));
        startCellColour->setAutoFillBackground(true);

        horizontalLayout_10->addWidget(startCellColour);

        label_5 = new QLabel(colorLegendGroupBox);
        label_5->setObjectName("label_5");

        horizontalLayout_10->addWidget(label_5);


        gridLayout->addLayout(horizontalLayout_10, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        visitedCellColour = new QWidget(colorLegendGroupBox);
        visitedCellColour->setObjectName("visitedCellColour");
        sizePolicy6.setHeightForWidth(visitedCellColour->sizePolicy().hasHeightForWidth());
        visitedCellColour->setSizePolicy(sizePolicy6);
        visitedCellColour->setMinimumSize(QSize(20, 20));
        visitedCellColour->setMaximumSize(QSize(20, 20));
        visitedCellColour->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(visitedCellColour);

        label_7 = new QLabel(colorLegendGroupBox);
        label_7->setObjectName("label_7");

        horizontalLayout_4->addWidget(label_7);


        gridLayout->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        currentCellColour = new QWidget(colorLegendGroupBox);
        currentCellColour->setObjectName("currentCellColour");
        sizePolicy6.setHeightForWidth(currentCellColour->sizePolicy().hasHeightForWidth());
        currentCellColour->setSizePolicy(sizePolicy6);
        currentCellColour->setMinimumSize(QSize(20, 20));
        currentCellColour->setMaximumSize(QSize(20, 20));
        currentCellColour->setAutoFillBackground(true);

        horizontalLayout_11->addWidget(currentCellColour);

        label_6 = new QLabel(colorLegendGroupBox);
        label_6->setObjectName("label_6");

        horizontalLayout_11->addWidget(label_6);


        gridLayout->addLayout(horizontalLayout_11, 2, 1, 1, 1);


        verticalLayout->addWidget(colorLegendGroupBox);

        resetButton = new QPushButton(verticalWidget);
        resetButton->setObjectName("resetButton");

        verticalLayout->addWidget(resetButton);

        exitButton = new QPushButton(verticalWidget);
        exitButton->setObjectName("exitButton");

        verticalLayout->addWidget(exitButton);


        horizontalLayout_2->addWidget(verticalWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "New maze file - Maze Solver", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as...", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        zoomLabel->setText(QCoreApplication::translate("MainWindow", "Zoom: 1.0x", nullptr));
        mazeParametersGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Maze Parameters", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Number of rows (3 - 60):", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Number of columns (3 - 60):", nullptr));
        generateButton->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        solveMethodGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Solve Method", nullptr));
        bfsRButton->setText(QCoreApplication::translate("MainWindow", "Breadth-First Search Algorithm", nullptr));
        dfsRButton->setText(QCoreApplication::translate("MainWindow", "Depth-First Search Algorithm", nullptr));
        aStarRButton->setText(QCoreApplication::translate("MainWindow", "A* Search", nullptr));
        solveButton->setText(QCoreApplication::translate("MainWindow", "Solve", nullptr));
        animationGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Animation", nullptr));
        animationSpeedLabel->setText(QCoreApplication::translate("MainWindow", " Speed: 100 (steps per second)", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        animationSpeedMaxLabel->setText(QCoreApplication::translate("MainWindow", "700", nullptr));
        animationPlayButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        visitedCellsLabel->setText(QCoreApplication::translate("MainWindow", "Visited cells: 0", nullptr));
        pathLengthLabel->setText(QCoreApplication::translate("MainWindow", "Path length: 0", nullptr));
        colorLegendGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Cell Colour Legend", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Not visited", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Finish", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Frontier", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Visited", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Current/Solution", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
