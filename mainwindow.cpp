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

    scene=new QGraphicsScene(this);
    graph=new plotGraph();
    ui->graphPlot->setScene(scene);
    QRect bound=ui->graphPlot->rect();
    scene->addItem(graph);
    scene->setSceneRect(bound);

    //Temporary. It has to be set automatically.
    graph->setXaxis(0,counter);
    graph->setYaxis(minData,maxData);
    graph->setXsticks(10);
    graph->setYsticks(5);
    graph->linkData(&storeData);

    //Connect new data signal.
    newData=connect(rawdata,&RS22812::newData,this,&MainWindow::addData);
    rData=connect(rawdata,&RS22812::newMode,this,&MainWindow::resetData);
}

MainWindow::~MainWindow()
{
    delete portPtr;
    delete ui;
    delete rawdata;
    delete lcd;
    delete scene;
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
    float val;
    try
    {
        val=rawdata->getVal();
    }catch(...)
    {
        return;
    }

    counter++;
    storeData.append(QPair<qreal,qreal>(counter,val));

    //Update axis. This is temporary. User will be given more control.
    graph->setXaxis(0,counter);
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
}

