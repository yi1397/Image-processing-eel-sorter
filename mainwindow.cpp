#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    bool success = false;

    ui->length_label->setFont(QFont("맑은 고딕", 18));
    ui->time_label->setFont(QFont("맑은 고딕", 18));

    success = camera_init(&main_cap, &cameraMatrix, &distCoeffs, VGA_MODE);

    if(success)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update_cam()));
        timer->start(10);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::update_cam()
{
    main_cap.read(cam_input);

    detection_result =
            detect_eel(cam_input, 160, 160);

    cv::cvtColor(cam_input, cam_input, cv::COLOR_BGR2RGB);

    qt_cam_img = QImage((const unsigned char*) (cam_input.data), cam_input.cols, cam_input.rows, QImage::Format_RGB888);
    ui->cam_label->setPixmap(QPixmap::fromImage(qt_cam_img));
    ui->cam_label->resize(ui->cam_label->pixmap()->size());

    ui->length_label->setText(QString("길이 : %1").arg(detection_result.length));

    ui->time_label->setText("실행시간 : " + QString::number((double)detection_result.response_time/1000) + "초");
}
