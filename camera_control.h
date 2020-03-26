#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H

#endif // CAMERA_CONTROL_H

#include <opencv2/opencv.hpp>

enum cam_modes
{
    NO_CAM_MODE = 0,
    qVGA_MODE = 320240,
    VGA_MODE = 640480
};

bool camera_init(
        cv::VideoCapture* cap,
        cv::Mat& cameraMatrix,
        cv::Mat& distCoeffs,
        cam_modes cam_mode
        )
{
    *cap = cv::VideoCapture(1 + cv::CAP_DSHOW);
    switch (cam_mode) {
    case qVGA_MODE:
    {
        cameraMatrix = (cv::Mat1d(3, 3) << 327.495, 0, 170.231, 0, 342.608, 120.341, 0, 0, 1);
        distCoeffs = (cv::Mat1d(1, 4) << -0.447434, 0.231295, 0.000754, -0.001325);

        cap->set(cv::CAP_PROP_FRAME_WIDTH, 640); // 카메라 영상 가로 크기 설정
        cap->set(cv::CAP_PROP_FRAME_HEIGHT, 480); // 카메라 영상 세로 크기 설정
        break;
    }
    case VGA_MODE:
    {
        cameraMatrix = (cv::Mat1d(3, 3) << 652.551, 0, 333.847, 0, 641.968, 234.218, 0, 0, 1);
        distCoeffs = (cv::Mat1d(1, 4) << -0.444277, 0.253481, 0.001623, 0.000861);

        cap->set(cv::CAP_PROP_FRAME_WIDTH, 320); // 카메라 영상 가로 크기 설정
        cap->set(cv::CAP_PROP_FRAME_HEIGHT, 240); // 카메라 영상 세로 크기 설정
        break;
    }
    default:
        return false;
    }
    return true;
}
