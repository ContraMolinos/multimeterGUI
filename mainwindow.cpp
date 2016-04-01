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

    lcd=new LCD(rawdata,this);
    ui->gridLayout->addWidget(lcd,0,0,1,1);

    connect(rawdata,SIGNAL(newData()),lcd,SLOT(update()));

    scene=new QGraphicsScene(this);
    graph=new plotGraph(scene);

    ui->graphPlot->setScene(scene);
    scene->addItem(graph);
    /*
    scene->setSceneRect(bound);
    qDebug()<<bound;*/

    //Temporary. It has to be set automatically.
    graph->setXaxis(0,counter);
    graph->setYaxis(minData,maxData);
    graph->setXsticks(10);
    graph->setYsticks(5);
    graph->linkData(&storeData);
    graph->setUnit(rawdata->getMode());

    //Connect new data signal.
    newData=connect(rawdata,&RS22812::newData,this,&MainWindow::addData);
    rData=connect(rawdata,&RS22812::newMode,this,&MainWindow::resetData);

    timeRunning=false;
    timeMark=new QElapsedTimer;
}

MainWindow::~MainWindow()
{
    delete portPtr;
    delete ui;
    delete rawdata;
    delete lcd;
    delete scene;
    delete timeMark;
}

void MainWindow::on_connectButton_clicked()
{
    portPtr->openPort(ui->comboBoxPort->currentText());
}

void MainWindow::on_disconnectButton_clicked()
{
    portPtr->closePort();
}

void MainWindow::addData()
{
    if(!timeRunning)
    {
        timeMark->start();
        timeRunning=true;
    }
    float val;
    try
    {
        val=rawdata->getVal();
    }catch(...)
    {
        return;
    }

    //counter++;
    //storeData.append(QPair<qreal,qreal>(counter,val));
    qint64 time=timeMark->elapsed();
    storeData.append(QPair<qint64,qreal>(time,val));
    //qDebug()<<timeMark->elapsed();

    //Update axis. This is temporary. User will be given more control.
    graph->setXaxis(0,time);
    if(val<minData)
    {
        minData=val;
        graph->setYaxis(minData,maxData);
    }else if(val>maxData)
    {
        maxData=val;
        graph->setYaxis(minData,maxData);
    }
    graph->update();
    ui->graphPlot->viewport()->update();
}

void MainWindow::resetData()
{
    storeData.clear();
    counter=0;
    minData=99999999;
    maxData=-99999999;
    graph->setUnit(rawdata->getMode());
    timeRunning=false;
}

