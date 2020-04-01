#include "setting_dialog.h"
#include "ui_setting_dialog.h"

setting_dialog::setting_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_dialog)
{
    ui->setupUi(this);
}

setting_dialog::~setting_dialog()
{
    delete ui;
}



void setting_dialog::on_confirm_Button_clicked()
{
    connect(this,SIGNAL(send_setting(int)), parent(), SLOT(get_setting(int)));

    emit send_setting(1000);
}
