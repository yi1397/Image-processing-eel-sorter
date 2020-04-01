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

void setting_dialog::get_setting_data(setting_data *set)
{
    set->detect_delay = ui->lineEdit_detect_delay->text().toUInt();
}

void setting_dialog::on_confirm_Button_clicked()
{
    setting_data user_setting;

    get_setting_data(&user_setting);

    connect(this,SIGNAL(send_setting(setting_data)), parent(), SLOT(get_setting(setting_data)));

    emit send_setting(user_setting);
}
