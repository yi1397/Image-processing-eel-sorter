#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H

#include <QImage>

#include <opencv2/opencv.hpp>

enum cam_modes
{
    NO_CAM_MODE = 0,
    qVGA_MODE = 320240,
    VGA_MODE = 640480
};


bool camera_init(
        cv::VideoCapture* cap,
        cv::Mat* cameraMatrix,
        cv::Mat* distCoeffs,
        cam_modes cam_mode
        );


#endif // CAMERA_CONTROL_H
