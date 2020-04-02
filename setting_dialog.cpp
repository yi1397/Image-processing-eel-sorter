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

void setting_dialog::get_setting_from_Mainwindow(setting_data set)
{
    user_setting = set;

    ui->lineEdit_detect_delay->setText(QString::number(user_setting.detect_delay));
}

void setting_dialog::get_setting_from_input(setting_data *set)
{
    set->detect_delay = ui->lineEdit_detect_delay->text().toUInt();
}

void setting_dialog::apply_setting()
{
    get_setting_from_input(&user_setting);

    connect(this,SIGNAL(send_setting(setting_data)), parent(), SLOT(get_setting(setting_data)));

    emit send_setting(user_setting);
}

void setting_dialog::on_pushButton_apply_clicked()
{
    apply_setting();
}

void setting_dialog::on_push_Button_confirm_clicked()
{
    apply_setting();
    this->close();
}

void setting_dialog::on_pushButton_cancel_clicked()
{
    this->close();
}
