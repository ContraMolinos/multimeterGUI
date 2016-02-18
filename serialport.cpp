/*!
  SerialPort

  Class to manage the communication with a serial port.

  RS 22-812 sends 9bytes long packets with the codified information.
  This class is meant to read those packets and send it to the RS22812
  class to store and interpret.
*/

#include "serialport.h"

#include <QDebug>

SerialPort::SerialPort(QObject *parent) : QObject(parent), isOpen(false)
{
    ports=new QSerialPortInfo();
    activePort=new QSerialPort(this);

}

SerialPort::~SerialPort()
{
    if(isOpen)
        closePort();
    delete ports;
}

/*!
 * \brief SerialPort::openPort
 * Opens a serial port for reading. If port name is empty, it does nothing.
 * If port name is not available. Does nothing and raises a warning.
 * \param portName  Name of the port as returned from QSerialPortInfo.
 * \return  If sucessful, returns 1. Else it returns 0;
 */
bool SerialPort::openPort(const QString portName)
{
    if(isOpen)  this->closePort();
    if(portName.isEmpty())  return 0;
    foreach(const QSerialPortInfo &p,listPorts())
    {
        if(p.portName()==portName)
        {
            activePort->setPort(p);
            if(activePort->open(MODE))
            {
                isOpen=true;

                //Set the communication parameters.
                activePort->setBaudRate(BAUDRATE);
                activePort->setDataBits(DATABITS);
                activePort->setParity(PARITY);
                activePort->setStopBits(STOPBITS);
                readConnect=connect(activePort,&QSerialPort::readyRead,this,&SerialPort::ready);
                return 1;
            }
            else
            {
                isOpen=false;
                QMessageBox::critical(NULL,"Port error","Error opening serial port.",QMessageBox::Ok);
                return 0;
            }
        }
    }
    isOpen=false;
    QMessageBox::critical(NULL,"Port error","Port name not found");
    return 0;
}

/*!
 * \brief SerialPort::closePort
 * \return
 */
bool SerialPort::closePort()
{
    if(isOpen)
    {
        activePort->close();
        QObject::disconnect(readConnect);
        return 1;
    }
    return 0;
}

/*!
 * \brief SerialPort::listPorts
 * Obtains and return the list of available ports.
 * \return QList<QSerialPortInfo>
 */
QList<QSerialPortInfo> SerialPort::listPorts()
{
    return ports->availablePorts();
}

/*!
 * \brief SerialPort::readPort
 * Reads the available data.
 */
void SerialPort::readPort()
{
    while(activePort->bytesAvailable()>9)
    {
        buffer=activePort->read(9);
    }
}

/*!
 * \brief SerialPort::ready
 * Re-emits the readyRead signal.
 */
void SerialPort::ready()
{
    readPort();
    emit readyRead(buffer);
}


