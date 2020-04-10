#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H

#include <QImage>

#include <opencv2/opencv.hpp>

#include "setting_control.h"

bool camera_init(
        cv::VideoCapture* cap,
        cv::Mat* cameraMatrix,
        cv::Mat* distCoeffs,
        setting_data* set
        );


#endif // CAMERA_CONTROL_H
