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
    void updateLabel(int _val);

    //To set the plot updating policy.
    void on_radioAutoRescaling_clicked();
    void on_radioFixed_clicked();
    void on_radioNoRescaling_clicked();

private:
    void updateAxes();
    Ui::MainWindow *ui;
    SerialPort *portPtr;
    RS22812 *rawdata;
    LCD *lcd;
    QLabel *label;
    plotGraph *graph;
    QGraphicsScene *scene;
    QList<QPair<qint64,qreal> > storeData;
    qint32 counter=0;

    QMetaObject::Connection newData;
    QMetaObject::Connection rData;

    QElapsedTimer *timeMark;
    bool timeRunning;

    enum UpdateMode {RESCALING, NORESCALING, FIXED} updateMode;

    //Temporal data
    QVector<QPair<qreal,qreal> >tmp;
};

#endif // MAINWINDOW_H
