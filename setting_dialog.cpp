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

void setting_dialog::on_pushButton_cancel_clicked()
{
    this->close();
}

void setting_dialog::on_pushButton_setting_load_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open File", "", "설정파일 (*.dat)");
    try {
        user_setting = get_setting_from_file(path.toStdString().c_str());
        put_data_to_lineEdit(user_setting);
        ui->lineEdit_loaded_setting->setText(path);
    } catch (const char* e_message) {
        QMessageBox::information(NULL, e_message, "파일이 잘못되었습니다");
    }
}

void setting_dialog::on_pushButton_make_new_settingfile_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,"다른이름으로 저장","", "설정파일 (*.dat)");
    try {
        get_setting_from_input(&user_setting);
        make_setting_file(path.toStdString().c_str(), &user_setting);
    } catch (const char* e_message) {
        QMessageBox::information(NULL, e_message, "저장할수 없음");
    }

}

void setting_dialog::on_pushButton_add_grade_clicked()
{
    QListWidgetItem* new_grade = new QListWidgetItem();

    QHBoxLayout* HLay = new QHBoxLayout();
    QLabel* Labed_grade_name = new QLabel(QString::number(ui->listWidget_grade->count() + 1) + "등급");
    QPushButton* PushButton_delete = new QPushButton();
    PushButton_delete->setText("삭제");
    HLay->addWidget(Labed_grade_name);
    HLay->addWidget(PushButton_delete);

    QWidget* grade_widget = new QWidget();
    grade_widget->setLayout(HLay);
    grade_widget->setFixedHeight(50);

    new_grade->setSizeHint(grade_widget->sizeHint());

    ui->listWidget_grade->addItem(new_grade);
    ui->listWidget_grade->setItemWidget(new_grade, grade_widget);
}
