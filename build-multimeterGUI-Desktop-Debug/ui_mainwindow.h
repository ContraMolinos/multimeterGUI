/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QVBoxLayout *verticalLayout;
    QLabel *labelPort;
    QComboBox *comboBoxPort;
    QGraphicsView *graphPlot;
    QGroupBox *auxGroupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioAutoRescaling;
    QRadioButton *radioNoRescaling;
    QRadioButton *radioFixed;
    QScrollBar *xAxisScrollBar;
    QLabel *xSliderValue;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(747, 430);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setContentsMargins(9, -1, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        verticalLayout_2->addWidget(connectButton);

        disconnectButton = new QPushButton(centralWidget);
        disconnectButton->setObjectName(QStringLiteral("disconnectButton"));

        verticalLayout_2->addWidget(disconnectButton);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelPort = new QLabel(centralWidget);
        labelPort->setObjectName(QStringLiteral("labelPort"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labelPort->setFont(font);
        labelPort->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelPort);

        comboBoxPort = new QComboBox(centralWidget);
        comboBoxPort->setObjectName(QStringLiteral("comboBoxPort"));

        verticalLayout->addWidget(comboBoxPort);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        graphPlot = new QGraphicsView(centralWidget);
        graphPlot->setObjectName(QStringLiteral("graphPlot"));
        graphPlot->setLineWidth(2);
        graphPlot->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphPlot->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout->addWidget(graphPlot, 1, 0, 1, 1);

        auxGroupBox = new QGroupBox(centralWidget);
        auxGroupBox->setObjectName(QStringLiteral("auxGroupBox"));
        auxGroupBox->setEnabled(true);
        layoutWidget = new QWidget(auxGroupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 20, 121, 83));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        radioAutoRescaling = new QRadioButton(layoutWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioAutoRescaling);
        radioAutoRescaling->setObjectName(QStringLiteral("radioAutoRescaling"));
        radioAutoRescaling->setChecked(true);

        verticalLayout_3->addWidget(radioAutoRescaling);

        radioNoRescaling = new QRadioButton(layoutWidget);
        buttonGroup->addButton(radioNoRescaling);
        radioNoRescaling->setObjectName(QStringLiteral("radioNoRescaling"));

        verticalLayout_3->addWidget(radioNoRescaling);

        radioFixed = new QRadioButton(layoutWidget);
        buttonGroup->addButton(radioFixed);
        radioFixed->setObjectName(QStringLiteral("radioFixed"));

        verticalLayout_3->addWidget(radioFixed);

        xAxisScrollBar = new QScrollBar(auxGroupBox);
        xAxisScrollBar->setObjectName(QStringLiteral("xAxisScrollBar"));
        xAxisScrollBar->setGeometry(QRect(10, 250, 160, 16));
        xAxisScrollBar->setOrientation(Qt::Horizontal);
        xSliderValue = new QLabel(auxGroupBox);
        xSliderValue->setObjectName(QStringLiteral("xSliderValue"));
        xSliderValue->setGeometry(QRect(90, 230, 31, 17));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(xSliderValue->sizePolicy().hasHeightForWidth());
        xSliderValue->setSizePolicy(sizePolicy1);
        xSliderValue->setFrameShape(QFrame::NoFrame);
        xSliderValue->setFrameShadow(QFrame::Plain);
        xSliderValue->setLineWidth(2);

        gridLayout->addWidget(auxGroupBox, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 747, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Multimeter GUI", 0));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", 0));
        disconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        labelPort->setText(QApplication::translate("MainWindow", "Select Port", 0));
        auxGroupBox->setTitle(QString());
        radioAutoRescaling->setText(QApplication::translate("MainWindow", "Auto resca&ling", 0));
        radioNoRescaling->setText(QApplication::translate("MainWindow", "Percentage &view", 0));
        radioFixed->setText(QApplication::translate("MainWindow", "Set origin", 0));
        xSliderValue->setText(QApplication::translate("MainWindow", "0", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
