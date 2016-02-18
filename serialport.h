/*!
  SerialPort

  Class to manage the communication with a serial port.

  RS 22-812 sends 9bytes long packets with the codified information.
  This class is meant to read those packets and send it to the RS22812
  class to store and interpret.
*/

#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QMessageBox>
#include <QByteArray>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    ~SerialPort();
    bool openPort(const QString portName);
    bool closePort();
    QList<QSerialPortInfo> listPorts();


private:
    QSerialPortInfo *ports;
    QSerialPort *activePort;

    bool isOpen;
    QByteArray buffer;

    QMetaObject::Connection readConnect;

    //Communication constants for the RS 22-812
    static const QSerialPort::BaudRate BAUDRATE=QSerialPort::Baud4800;
    static const QSerialPort::DataBits DATABITS=QSerialPort::Data8;
    static const QSerialPort::StopBits STOPBITS=QSerialPort::OneStop;
    static const QSerialPort::Parity PARITY=QSerialPort::NoParity;
    const QSerialPort::OpenMode MODE=QSerialPort::ReadOnly;

    void readPort();

signals:
    void readyRead(QByteArray buffer);

public slots:
    void ready();
};

#endif // SERIALPORT_H
