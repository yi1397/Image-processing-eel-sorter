#ifndef SERIAL_CONTROL_H
#define SERIAL_CONTROL_H

#include <QtSerialPort>

class serial_control
{
public:
    serial_control();

    bool set_port();

    void send_data(QString data);
private:
    QSerialPort* port;
};

#endif // SERIAL_CONTROL_H
