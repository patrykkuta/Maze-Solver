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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
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
    QAction *actionInfo;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton_4;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSlider *horizontalSlider;
    QLabel *label_5;
    QPushButton *pushButton_5;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QSlider *horizontalSlider_2;
    QLabel *label_9;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLabel *label_7;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1000, 670);
        MainWindow->setMinimumSize(QSize(800, 670));
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
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName("actionInfo");
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
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMinimumSize(QSize(0, 192));
        graphicsView->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_2->addWidget(graphicsView);

        verticalWidget = new QWidget(centralwidget);
        verticalWidget->setObjectName("verticalWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(verticalWidget->sizePolicy().hasHeightForWidth());
        verticalWidget->setSizePolicy(sizePolicy2);
        verticalWidget->setMinimumSize(QSize(280, 0));
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, -1, 5, -1);
        groupBox = new QGroupBox(verticalWidget);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy4);

        horizontalLayout_5->addWidget(label);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(3);
        spinBox->setMaximum(25);
        spinBox->setValue(5);

        horizontalLayout_5->addWidget(spinBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        sizePolicy4.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(label_2);

        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName("spinBox_2");
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
        spinBox_2->setSizePolicy(sizePolicy5);
        spinBox_2->setMinimum(3);
        spinBox_2->setMaximum(25);
        spinBox_2->setValue(5);

        horizontalLayout_3->addWidget(spinBox_2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(groupBox);

        pushButton_3 = new QPushButton(verticalWidget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        groupBox_2 = new QGroupBox(verticalWidget);
        groupBox_2->setObjectName("groupBox_2");
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy6);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName("radioButton");
        radioButton->setChecked(true);

        verticalLayout_3->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName("radioButton_2");

        verticalLayout_3->addWidget(radioButton_2);


        verticalLayout->addWidget(groupBox_2);

        pushButton_4 = new QPushButton(verticalWidget);
        pushButton_4->setObjectName("pushButton_4");

        verticalLayout->addWidget(pushButton_4);

        groupBox_3 = new QGroupBox(verticalWidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(40);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName("label_6");
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);
        label_6->setAlignment(Qt::AlignCenter);
        label_6->setMargin(7);

        verticalLayout_5->addWidget(label_6);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(5, -1, 10, -1);
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        horizontalSlider = new QSlider(groupBox_3);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(50);
        horizontalSlider->setValue(10);
        horizontalSlider->setTracking(true);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        horizontalSlider->setTickPosition(QSlider::NoTicks);
        horizontalSlider->setTickInterval(1);

        horizontalLayout_6->addWidget(horizontalSlider);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");

        horizontalLayout_6->addWidget(label_5);


        verticalLayout_5->addLayout(horizontalLayout_6);

        pushButton_5 = new QPushButton(groupBox_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setFlat(false);

        verticalLayout_5->addWidget(pushButton_5);


        verticalLayout_4->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setMargin(4);

        verticalLayout_6->addWidget(label_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");

        horizontalLayout_8->addWidget(label_10);

        horizontalSlider_2 = new QSlider(groupBox_3);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(horizontalSlider_2);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");

        horizontalLayout_8->addWidget(label_9);


        verticalLayout_6->addLayout(horizontalLayout_8);


        verticalLayout_4->addLayout(verticalLayout_6);


        verticalLayout->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_8 = new QLabel(verticalWidget);
        label_8->setObjectName("label_8");
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(label_8);

        label_7 = new QLabel(verticalWidget);
        label_7->setObjectName("label_7");
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_7);


        verticalLayout->addLayout(horizontalLayout_7);

        pushButton_2 = new QPushButton(verticalWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(verticalWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);


        horizontalLayout_2->addWidget(verticalWidget);

        horizontalLayout_2->setStretch(0, 2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionInfo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Maze Solver", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save...", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as...", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open...", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New...", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionInfo->setText(QCoreApplication::translate("MainWindow", "How it works", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Maze Parameters", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Number of rows (3 - 25):", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Number of columns (3 - 25):", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Solve Method", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Breadth-First Search Algorithm", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Depth-First Search Algorithm", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Solve", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Animation", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", " Speed: x (cells per second)", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Pause/Resume", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Playback (Step by step)", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Visited cells:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Path length:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
