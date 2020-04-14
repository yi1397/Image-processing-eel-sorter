#include "serial_dialog.h"
#include "ui_serial_dialog.h"

serial_Dialog::serial_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serial_Dialog)
{
    ui->setupUi(this);
}

serial_Dialog::~serial_Dialog()
{
    delete ui;
}
