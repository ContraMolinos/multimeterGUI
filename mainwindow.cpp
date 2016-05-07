#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

/*!
 * \brief MainWindow::MainWindow. Constructor
 * \param parent
 * The main window constructor will, in addition to create the corresponding subwidgets, populate the list of available ports and connect signals with slots.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    /// \todo: Temporary. It has to be set automatically.
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

/*!
 * \brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete portPtr;
    delete ui;
    delete rawdata;
    delete lcd;
    delete scene;
    delete timeMark;
}

/*!
 * \brief MainWindow::addData. Add new data to the data set.
 * This method will be called when new data has been read from the serial port, it will add the new value to the stored set of pairs (time,value) and update the graph.
 */
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

    qint64 time=timeMark->elapsed();
    storeData.append(QPair<qint64,qreal>(time,val));

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

/*!
 * \brief MainWindow::resetData. Resets the data stored in memory.
 * This method is called when the multimeter's mode changes, clearing all the data stored in memory.
 */
void MainWindow::resetData()
{
    storeData.clear();
    counter=0;
    minData=99999999;
    maxData=-99999999;
    graph->setUnit(rawdata->getMode());
    timeRunning=false;
}

/*!
 * \brief MainWindow::on_connectButton_clicked. Open the selected port.
 */
void MainWindow::on_connectButton_clicked()
{
    portPtr->openPort(ui->comboBoxPort->currentText());
}

/*!
 * \brief MainWindow::on_disconnectButton_clicked. Disconnect from the current port.
 */
void MainWindow::on_disconnectButton_clicked()
{
    portPtr->closePort();
}

