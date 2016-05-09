#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

/*!
 * \brief Constructor
 * \param parent
 * The main window constructor will, in addition to create the corresponding subwidgets, populate the list of available ports and connect signals with slots.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->auxGroupBox->setStyleSheet("border:0;");
    ui->xAxisScrollBar->setDisabled(true); //By default the plot will update automatically.
    updateMode=RESCALING;
    ui->xSliderValue->setVisible(false);
    //Link the slider with the label.
    connect(ui->xAxisScrollBar,SIGNAL(valueChanged(int)),this,SLOT(updateLabel(int)));

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

    // Initial settings of the plot.
    graph->setXaxis(0,counter);
    graph->setYaxis(0,1);
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
 * \brief Destructor.
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
 * \brief Add new data to the data set.
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

    updateAxes();
}

/*!
 * \brief Resets the data stored in memory.
 * This method is called when the multimeter's mode changes, clearing all the data stored in memory.
 */
void MainWindow::resetData()
{
    storeData.clear();
    counter=0;
    graph->setUnit(rawdata->getMode());
    graph->setXaxis(0,1);
    ui->xAxisScrollBar->setValue(0);
    ui->xAxisScrollBar->setRange(0,graph->getXMax());
    timeRunning=false;
}

/*!
 * \brief Slot to update the value shown in the scroll bar label.
 * \param _val
 */
void MainWindow::updateLabel(int _val)
{
    QString displayString;
    if(updateMode==NORESCALING)
        displayString=QString::number(100-_val)+"%";
    else if(updateMode==FIXED)
        displayString=QString::number(static_cast<float>(_val)/1000,'f',2)+"s.";
    qint8 newWidth=(ui->xSliderValue->fontMetrics()).width(displayString);
    ui->xSliderValue->resize(newWidth,ui->xSliderValue->height());
    ui->xSliderValue->setText(displayString);
}

/*!
 * \brief Opens the selected port.
 */
void MainWindow::on_connectButton_clicked()
{
    portPtr->openPort(ui->comboBoxPort->currentText());
}

/*!
 * \brief Disconnect from the current port.
 */
void MainWindow::on_disconnectButton_clicked()
{
    portPtr->closePort();
}

/*!
 * \brief Sets the plot to rescale automatically.
 */
void MainWindow::on_radioAutoRescaling_clicked()
{
    ui->xAxisScrollBar->setDisabled(true);  //If the plot updates automatically, the scroll bar isn't needed.
    ui->xSliderValue->setVisible(false);
    updateMode=RESCALING;
}
/*!
 * \brief Sets the plot to a fixed interval.
 */
void MainWindow::on_radioFixed_clicked()
{
    ui->xAxisScrollBar->setDisabled(false); //Enables the scroll bar.
    ui->xSliderValue->setVisible(true);
    ui->xAxisScrollBar->setValue(0);    //Reset the bar position.
    updateLabel(0);                     //Reset the label.
    ui->xAxisScrollBar->setRange(0,graph->getXMax());
    updateMode=FIXED;
}
/*!
 * \brief Sets the plot to an interval of fixed size.
 */
void MainWindow::on_radioNoRescaling_clicked()
{
    ui->xAxisScrollBar->setDisabled(false); //Enables the scroll bar.
    ui->xSliderValue->setVisible(true);
    ui->xAxisScrollBar->setValue(0);        //Reset the bar position.
    updateLabel(0);                         //Reset the label.
    ui->xAxisScrollBar->setRange(0,100);
    updateMode=NORESCALING;
}

/*!
 * \brief Reset the maximum and minimum values of the plot axes.
 */
void MainWindow::updateAxes()
{
    qint64 time=storeData.last().first;
    float val;
    qreal minData=99999999;
    qreal maxData=-99999999;
    //Update axis.
    quint32 xMinVal;
    switch(updateMode)
    {
        case RESCALING:
            xMinVal=0;
            break;
        case NORESCALING:
            xMinVal=ui->xAxisScrollBar->value()*time/100;
            break;
        case FIXED:
            xMinVal=ui->xAxisScrollBar->value();
            break;
        default:
            qDebug()<<"Error setting x axis limits";
            exit(1);
    }

    graph->setXaxis(xMinVal,time);
    if(updateMode==FIXED)
        ui->xAxisScrollBar->setRange(0,graph->getXMax());   //Update the max value shown in the scroll bar.
    for(QList<QPair<qint64,qreal> >::iterator it=storeData.begin();it!=storeData.end();++it)
    {
        if((*it).first>=xMinVal)
        {
            val=(*it).second;
            if(val<minData)
                minData=val;
            if(val>maxData)
                maxData=val;
        }
        graph->setYaxis(minData,maxData);
    }

    graph->setYaxis(minData,maxData);
    graph->update();
    ui->graphPlot->viewport()->update();
}

