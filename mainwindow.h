#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "serialport.h"
#include "rs22812.h"
#include "lcd.h"

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

private:
    Ui::MainWindow *ui;
    SerialPort *portPtr;
    RS22812 *rawdata;
    LCD *lcd;
    QLabel *label;
};

#endif // MAINWINDOW_H
