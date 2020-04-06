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

void setting_dialog::put_data_to_lineEdit(setting_data set)
{
    user_setting = set;

    ui->lineEdit_detect_saturation->setText(QString::number(user_setting.saturation));
    ui->lineEdit_detect_size->setText(QString::number(user_setting.min_size_to_detect));
    ui->lineEdit_detect_delay->setText(QString::number(user_setting.detect_delay));
    ui->lineEdit_detect_smoothing->setText(QString::number(user_setting.smoothing));
}

void setting_dialog::get_setting_from_input(setting_data *set)
{


    int saturation = ui->lineEdit_detect_saturation->text().toUInt();
    int min_size_to_detect = ui->lineEdit_detect_size->text().toInt();
    int detect_delay = ui->lineEdit_detect_delay->text().toUInt();
    int smoothing = ui->lineEdit_detect_smoothing->text().toInt();

    if(smoothing % 2 ==0) throw "윤곽선 스무딩의 값은 홀수여야합니다";

    set->saturation = saturation;
    set->min_size_to_detect = min_size_to_detect;
    set->detect_delay = detect_delay;
    set->smoothing = smoothing;
}

void setting_dialog::apply_setting()
{
    get_setting_from_input(&user_setting);

    connect(this,SIGNAL(send_setting(setting_data)), parent(), SLOT(get_setting(setting_data)));

    emit send_setting(user_setting);

    make_setting_file("D:/eel_sorter/eel_sorter/set.dat", &user_setting);
}

void setting_dialog::on_pushButton_apply_clicked()
{
    try {
        apply_setting();

    } catch (const char* e_message) {
        QMessageBox::information(this,"올바르지않은 설정", e_message);
    }
}

void setting_dialog::on_push_Button_confirm_clicked()
{
    try {
        apply_setting();
        this->close();

    } catch (const char* e_message) {
        QMessageBox::information(this,"올바르지않은 설정", e_message);
    }
}

void setting_dialog::on_pushButton_setting_load_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), tr(""), tr("Text (*.dat)"));
    try {
        user_setting = get_setting_from_file(path.toStdString().c_str());
        put_data_to_lineEdit(user_setting);
    } catch (const char* e_message) {
        QMessageBox::information(NULL, e_message, "파일이 잘못되었습니다");
    }
}
