#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    bool success = true;

    main_cap = cv::VideoCapture(0 + cv::CAP_DSHOW);

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
    cv::cvtColor(cam_input, cam_input, cv::COLOR_BGR2RGB);
    qt_cam_img = QImage((const unsigned char*) (cam_input.data), cam_input.cols, cam_input.rows, QImage::Format_RGB888);
    ui->cam_label->setPixmap(QPixmap::fromImage(qt_cam_img));
    ui->cam_label->resize(ui->cam_label->pixmap()->size());
}
