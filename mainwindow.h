#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "camera_control.h"
#include "eel_detect.h"
#include "setting_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void update_cam();

private:
    Ui::MainWindow *ui;

    setting_dialog *setting_dialo;

    QTimer *timer;
    cv::VideoCapture main_cap;
    cv::Mat cam_input;
    QImage qt_cam_img;

    eel_data detection_result;

    cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64FC1);
    cv::Mat distCoeffs = cv::Mat::zeros(1, 5, CV_64FC1);;
};
#endif // MAINWINDOW_H
