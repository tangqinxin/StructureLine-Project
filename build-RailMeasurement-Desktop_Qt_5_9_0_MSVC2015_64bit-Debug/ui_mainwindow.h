/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_RailWayFig;
    QLabel *label_LUArrowFig;
    QLabel *label_LDArrowFig;
    QLabel *label_RUArrowFig;
    QLabel *label_RDArrowFig;
    QLabel *label_DArrowFig;
    QPushButton *pushButton_Measure;
    QPushButton *pushButton_ChangeToCamWin1;
    QCustomPlot *widget_LUArrowFig;
    QPushButton *pushButton_ChangeToCamWin2;
    QPushButton *pushButton_ChangeToCamWin3;
    QPushButton *pushButton_ChangeToCamWin4;
    QPushButton *pushButton_ChangeToCamWin5;
    QCustomPlot *widget_LDArrowFig;
    QCustomPlot *widget_DownArrowFig;
    QCustomPlot *widget_RUArrowFig;
    QCustomPlot *widget_RDArrowFig;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1920, 1080);
        MainWindow->setMinimumSize(QSize(1920, 1080));
        MainWindow->setMaximumSize(QSize(1920, 1080));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_RailWayFig = new QLabel(centralWidget);
        label_RailWayFig->setObjectName(QStringLiteral("label_RailWayFig"));
        label_RailWayFig->setGeometry(QRect(367, 1, 400, 400));
        label_RailWayFig->setMinimumSize(QSize(400, 400));
        label_RailWayFig->setMaximumSize(QSize(400, 400));
        label_RailWayFig->setPixmap(QPixmap(QString::fromUtf8("../image/RailWayFigure.png")));
        label_RailWayFig->setScaledContents(true);
        label_LUArrowFig = new QLabel(centralWidget);
        label_LUArrowFig->setObjectName(QStringLiteral("label_LUArrowFig"));
        label_LUArrowFig->setGeometry(QRect(340, 160, 200, 50));
        label_LUArrowFig->setPixmap(QPixmap(QString::fromUtf8("../image/\347\256\255\345\244\264.png")));
        label_LUArrowFig->setScaledContents(true);
        label_LDArrowFig = new QLabel(centralWidget);
        label_LDArrowFig->setObjectName(QStringLiteral("label_LDArrowFig"));
        label_LDArrowFig->setGeometry(QRect(330, 350, 40, 50));
        label_LDArrowFig->setPixmap(QPixmap(QString::fromUtf8("../image/\347\256\255\345\244\264.png")));
        label_LDArrowFig->setScaledContents(true);
        label_RUArrowFig = new QLabel(centralWidget);
        label_RUArrowFig->setObjectName(QStringLiteral("label_RUArrowFig"));
        label_RUArrowFig->setGeometry(QRect(610, 160, 200, 50));
        label_RUArrowFig->setPixmap(QPixmap(QString::fromUtf8("../image/\347\256\255\345\244\264\345\220\221\345\267\246.png")));
        label_RUArrowFig->setScaledContents(true);
        label_RDArrowFig = new QLabel(centralWidget);
        label_RDArrowFig->setObjectName(QStringLiteral("label_RDArrowFig"));
        label_RDArrowFig->setGeometry(QRect(770, 350, 40, 50));
        label_RDArrowFig->setPixmap(QPixmap(QString::fromUtf8("../image/\347\256\255\345\244\264\345\220\221\345\267\246.png")));
        label_RDArrowFig->setScaledContents(true);
        label_DArrowFig = new QLabel(centralWidget);
        label_DArrowFig->setObjectName(QStringLiteral("label_DArrowFig"));
        label_DArrowFig->setGeometry(QRect(550, 400, 40, 30));
        label_DArrowFig->setPixmap(QPixmap(QString::fromUtf8("../image/\347\256\255\345\244\264\345\220\221\344\270\212.png")));
        label_DArrowFig->setScaledContents(true);
        pushButton_Measure = new QPushButton(centralWidget);
        pushButton_Measure->setObjectName(QStringLiteral("pushButton_Measure"));
        pushButton_Measure->setGeometry(QRect(1300, 150, 200, 80));
        pushButton_ChangeToCamWin1 = new QPushButton(centralWidget);
        pushButton_ChangeToCamWin1->setObjectName(QStringLiteral("pushButton_ChangeToCamWin1"));
        pushButton_ChangeToCamWin1->setGeometry(QRect(1300, 240, 200, 80));
        widget_LUArrowFig = new QCustomPlot(centralWidget);
        widget_LUArrowFig->setObjectName(QStringLiteral("widget_LUArrowFig"));
        widget_LUArrowFig->setGeometry(QRect(30, 30, 300, 300));
        pushButton_ChangeToCamWin2 = new QPushButton(centralWidget);
        pushButton_ChangeToCamWin2->setObjectName(QStringLiteral("pushButton_ChangeToCamWin2"));
        pushButton_ChangeToCamWin2->setGeometry(QRect(1300, 330, 200, 80));
        pushButton_ChangeToCamWin3 = new QPushButton(centralWidget);
        pushButton_ChangeToCamWin3->setObjectName(QStringLiteral("pushButton_ChangeToCamWin3"));
        pushButton_ChangeToCamWin3->setGeometry(QRect(1300, 420, 200, 80));
        pushButton_ChangeToCamWin4 = new QPushButton(centralWidget);
        pushButton_ChangeToCamWin4->setObjectName(QStringLiteral("pushButton_ChangeToCamWin4"));
        pushButton_ChangeToCamWin4->setGeometry(QRect(1300, 510, 200, 80));
        pushButton_ChangeToCamWin5 = new QPushButton(centralWidget);
        pushButton_ChangeToCamWin5->setObjectName(QStringLiteral("pushButton_ChangeToCamWin5"));
        pushButton_ChangeToCamWin5->setGeometry(QRect(1300, 600, 200, 80));
        widget_LDArrowFig = new QCustomPlot(centralWidget);
        widget_LDArrowFig->setObjectName(QStringLiteral("widget_LDArrowFig"));
        widget_LDArrowFig->setGeometry(QRect(30, 350, 300, 300));
        widget_DownArrowFig = new QCustomPlot(centralWidget);
        widget_DownArrowFig->setObjectName(QStringLiteral("widget_DownArrowFig"));
        widget_DownArrowFig->setGeometry(QRect(420, 440, 300, 300));
        widget_RUArrowFig = new QCustomPlot(centralWidget);
        widget_RUArrowFig->setObjectName(QStringLiteral("widget_RUArrowFig"));
        widget_RUArrowFig->setGeometry(QRect(830, 30, 300, 300));
        widget_RDArrowFig = new QCustomPlot(centralWidget);
        widget_RDArrowFig->setObjectName(QStringLiteral("widget_RDArrowFig"));
        widget_RDArrowFig->setGeometry(QRect(830, 360, 300, 300));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_RailWayFig->setText(QString());
        label_LUArrowFig->setText(QString());
        label_LDArrowFig->setText(QString());
        label_RUArrowFig->setText(QString());
        label_RDArrowFig->setText(QString());
        label_DArrowFig->setText(QString());
        pushButton_Measure->setText(QApplication::translate("MainWindow", "\346\265\213\351\207\217\347\273\223\346\236\234", Q_NULLPTR));
        pushButton_ChangeToCamWin1->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\345\210\260\347\233\270\346\234\2721", Q_NULLPTR));
        pushButton_ChangeToCamWin2->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\345\210\260\347\233\270\346\234\2722", Q_NULLPTR));
        pushButton_ChangeToCamWin3->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\345\210\260\347\233\270\346\234\2723", Q_NULLPTR));
        pushButton_ChangeToCamWin4->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\345\210\260\347\233\270\346\234\2724", Q_NULLPTR));
        pushButton_ChangeToCamWin5->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\345\210\260\347\233\270\346\234\2725", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
