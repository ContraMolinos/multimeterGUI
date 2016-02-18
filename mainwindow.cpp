/*!
  Multimeter GUI

  GUI for the RS-232 mode of the Radio Shack 22-812.

  FJS. 2016.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->lcdDisplay->setStyleSheet("QLabel {background-color:white;}");

    //Looks for available ports and populate the combo box
    ui->comboBoxPort->addItem("");  //Empty item to be the default at the beginning.
    portPtr=new SerialPort(this);
    foreach(const QSerialPortInfo &p,portPtr->listPorts())
    {
        ui->comboBoxPort->addItem(p.portName());
    }

    //Decode RS22-812 data
    rawdata=new RS22812(this);

    connect(portPtr,SIGNAL(readyRead(QByteArray)),rawdata,SLOT(newValue(QByteArray)));

    //lcd=new LCD(rawdata,ui->lcdDisplay);
    lcd=new LCD(rawdata,this);

    connect(rawdata,SIGNAL(newData()),lcd,SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete portPtr;
    delete ui;
    delete rawdata;
    delete lcd;
}

void MainWindow::on_connectButton_clicked()
{
    portPtr->openPort(ui->comboBoxPort->currentText());
}

void MainWindow::on_disconnectButton_clicked()
{
    portPtr->closePort();
}

