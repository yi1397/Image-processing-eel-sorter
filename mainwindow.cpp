    #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    bool success = false;

    ui->centralwidget->setStyleSheet("background-color : white");

    ui->time_name->setFont(QFont("맑은 고딕", 18));
    ui->time_name->setStyleSheet("background-color : #58D3F7;"
                                 "color : balck;"
                                 "border-style: solid;"
                                 "border-width: 2px;"
                                 "border-color: black;"
                                 "border-radius: 3px");
    ui->time_name->setAlignment(Qt::AlignCenter);

    ui->time_show->setFont(QFont("맑은 고딕", 18));
    ui->time_show->setStyleSheet("background-color : #CEF6F5;"
                                 "color : balck;"
                                 "border-style: solid;"
                                 "border-width: 2px;"
                                 "border-color: black;"
                                 "border-radius: 3px");
    ui->time_show->setAlignment(Qt::AlignCenter);

    ui->length_name->setFont(QFont("맑은 고딕", 18));
    ui->length_name->setStyleSheet("background-color : #58D3F7;"
                                   "color : balck;"
                                   "border-style: solid;"
                                   "border-width: 2px;"
                                   "border-color: black;"
                                   "border-radius: 3px");
    ui->length_name->setAlignment(Qt::AlignCenter);

    ui->length_show->setFont(QFont("맑은 고딕", 18));
    ui->length_show->setStyleSheet("background-color : #CEF6F5;"
                                   "color : balck;"
                                   "border-style: solid;"
                                   "border-width: 2px;"
                                   "border-color: black;"
                                   "border-radius: 3px");
    ui->length_show->setAlignment(Qt::AlignCenter);

    success = camera_init(&main_cap, &cameraMatrix, &distCoeffs, VGA_MODE);

    if(success)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(find_eel()));
        timer->start(10);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    setting_dialo = new setting_dialog(this);
    setting_dialo->setModal(true);
    setting_dialo->show();
}

void MainWindow::find_eel()
{
    main_cap.read(cam_input);

    if(detect_eel(cam_input, 0, 160, 10000) && !detected)
    {
        detected = true;
        QTimer::singleShot(detect_delay, this, SLOT(update_eel()));

    }

}

void MainWindow::update_eel()
{
    main_cap.read(cam_input);

    detection_result =
            measure_eel_length(cam_input, 0, 160);

    ui->length_show->setText(QString("%1 cm").arg(detection_result.length));

    ui->time_show->setText(QString::number((double)detection_result.response_time/1000) + "초");

    cv::cvtColor(cam_input, cam_input, cv::COLOR_BGR2RGB);

    qt_cam_img = QImage((const unsigned char*) (cam_input.data), cam_input.cols, cam_input.rows, QImage::Format_RGB888);
    ui->cam_label->setPixmap(QPixmap::fromImage(qt_cam_img).scaled(ui->cam_label->width(), ui->cam_label->height(), Qt::KeepAspectRatio));
    //ui->cam_label->resize(ui->cam_label->pixmap()->size());

    detected = false;
}
