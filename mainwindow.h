#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "camera_control.h"
#include "eel_detect.h"
#include "setting_dialog.h"
#include "setting_control.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void send_setting(setting_data set);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void get_setting(setting_data set);

private slots:
    void find_eel();

    void update_eel();

    void on_pushButton_setting_clicked();

private:
    Ui::MainWindow *ui;

    setting_data user_setting;

    setting_dialog *setting_dialo;

    void count_eel(eel_data data);

    QTimer *timer;
    cv::VideoCapture main_cap;
    cv::Mat cam_input;
    QImage qt_cam_img;

    eel_data detection_result;

    cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64FC1);
    cv::Mat distCoeffs = cv::Mat::zeros(1, 5, CV_64FC1);;

    bool detected = false;

    clock_t begin_t, end_t;
};
#endif // MAINWINDOW_H
