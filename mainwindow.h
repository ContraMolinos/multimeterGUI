#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "serialport.h"
#include "rs22812.h"
#include "lcd.h"
#include "plotgraph.h"

#include <QPair>
#include <QElapsedTimer>

namespace Ui {
class MainWindow;
}

/*! \class MainWindow
 * \brief The MainWindow class.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void addData();
    void resetData();

private:
    Ui::MainWindow *ui;
    SerialPort *portPtr;
    RS22812 *rawdata;
    LCD *lcd;
    QLabel *label;
    plotGraph *graph;
    QGraphicsScene *scene;
    QVector<QPair<qint64,qreal> > storeData;
    qint32 counter=0;
    qreal minData=99999999;
    qreal maxData=-99999999;

    QMetaObject::Connection newData;
    QMetaObject::Connection rData;

    QElapsedTimer *timeMark;
    bool timeRunning;

    //Temporal data
    QVector<QPair<qreal,qreal> >tmp;
};

#endif // MAINWINDOW_H
