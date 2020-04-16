#ifndef SERIAL_CONTROL_H
#define SERIAL_CONTROL_H

#include <QtSerialPort>

class serial_control
{
public:
    serial_control();

    bool set_port(QString* portName);

    void send_data(QString data);

    static QStringList find_port();
private:
    QSerialPort* port;
};

#endif // SERIAL_CONTROL_H
