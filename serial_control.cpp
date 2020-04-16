#include "serial_control.h"

serial_control::serial_control()
{
    port = new QSerialPort();
}

bool serial_control::set_port(QString portName)
{
    delete port;
    port = new QSerialPort();
    port->setPortName(portName);
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    if(!port->open(QIODevice::ReadWrite)) return false;

    return true;
}

void serial_control::send_data(QString data)
{
    port->write(data.toStdString().c_str());
}

QStringList serial_control::find_port()
{
    QStringList portNames;
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {

        portNames.append(serialPortInfo.portName());
    }
    return portNames;
}
