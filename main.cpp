#include "mainwindow.h"
#include "camera_control.h"

#include <QApplication>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    cv::VideoCapture main_cam;

    cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64FC1);
    cv::Mat distCoeffs = cv::Mat::zeros(1, 5, CV_64FC1);;

    bool success;
    success= camera_init(&main_cam, cameraMatrix, distCoeffs, qVGA_MODE);

    if(!success)
    {
        return -1;
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
