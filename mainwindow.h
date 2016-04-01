/*! Multimeter GUI
 * GUI for the RS-232 mode of the Radio Shack 22-812.
   Copyright (C) 2016  FJ Salguero

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
