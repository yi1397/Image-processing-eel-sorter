#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    bool success = false;

    try {
        user_setting = get_setting_from_file("D:/eel_sorter/eel_sorter/set.dat");
    } catch (const char* e_message) {
        QMessageBox::information(NULL, e_message, "설정파일을 재설정합니다");
        make_setting_file("D:/eel_sorter/eel_sorter/set.dat", &user_setting);
    }

    success = camera_init(&main_cap, &cameraMatrix, &distCoeffs, VGA_MODE);

    if(success)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(find_eel()));
        timer->start(0);
    }
    set_result_table();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::get_setting(setting_data set)
{
    user_setting = set;
    set_result_table();
}


void MainWindow::find_eel()
{
    if(detected) return;
    begin_t = clock();
    main_cap.read(cam_input);

    if(detect_eel(cam_input, &user_setting))
    {
        detected = true;
        QTimer::singleShot(user_setting.detect_delay, this, SLOT(update_eel()));

    }

}

void MainWindow::update_eel()
{
    eel_count++;

    cv::Mat detect_img;
    cv::undistort(cam_input, detect_img, cameraMatrix, distCoeffs);

    detection_result =
            measure_eel_length(detect_img, &user_setting);

    ui->length_show->setText(QString("%1 cm").arg(detection_result.length));


    end_t = clock();

    //ui->time_show->setText(QString::number((double)end_t - begin_t) + "초");

    ui->time_show->setText(QString::number((double)detection_result.response_time/1000) + "초");

    ui->count_show->setText(QString::number(eel_count));

    cv::cvtColor(detect_img, detect_img, cv::COLOR_BGR2RGB);

    qt_cam_img = QImage((const unsigned char*) (detect_img.data), detect_img.cols, detect_img.rows, QImage::Format_RGB888);
    ui->cam_label->setPixmap(QPixmap::fromImage(qt_cam_img).scaled(ui->cam_label->width(), ui->cam_label->height(), Qt::KeepAspectRatio));
    //ui->cam_label->resize(ui->cam_label->pixmap()->size());

    detected = false;
}

void MainWindow::set_result_table()
{
    ui->tableWidget_result->setAlternatingRowColors(true);
    ui->tableWidget_result->setColumnCount(2);
    ui->tableWidget_result->setHorizontalHeaderLabels(QString("등급;수량").split(";"));
    ui->tableWidget_result->setRowCount(user_setting.ratings.count());
    for(int i=0; i < user_setting.ratings.count(); ++i)
    {
        ui->tableWidget_result->setItem(i, 0, new QTableWidgetItem(QString::number(i+1) + "등급"));
    }
}

void MainWindow::on_pushButton_setting_clicked()
{
    setting_dialo = new setting_dialog(this);
    setting_dialo->setModal(true);
    setting_dialo->show();

    connect(this,SIGNAL(send_setting(setting_data)), setting_dialo, SLOT(put_data_to_lineEdit(setting_data)));

    emit send_setting(user_setting);

}

void MainWindow::count_eel(eel_data data)
{

}
