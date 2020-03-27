#include "camera_control.h"

bool camera_init(
        cv::VideoCapture* cap,
        cv::Mat* cameraMatrix,
        cv::Mat* distCoeffs,
        cam_modes cam_mode
        )
{
    *cap = cv::VideoCapture(0 + cv::CAP_DSHOW);
    
    switch (cam_mode) {
    case qVGA_MODE:
    {
        cap->set(cv::CAP_PROP_FRAME_WIDTH, 320); // 카메라 영상 가로 크기 설정
        cap->set(cv::CAP_PROP_FRAME_HEIGHT, 240); // 카메라 영상 세로 크기 설정

        *cameraMatrix = (cv::Mat1d(3, 3) << 327.495, 0, 170.231, 0, 342.608, 120.341, 0, 0, 1);
        *distCoeffs = (cv::Mat1d(1, 4) << -0.447434, 0.231295, 0.000754, -0.001325);
        // 카메라 캘리브레이션을 위한 데이터
        break;
    }
    case VGA_MODE:
    {
        cap->set(cv::CAP_PROP_FRAME_WIDTH, 640); // 카메라 영상 가로 크기 설정
        cap->set(cv::CAP_PROP_FRAME_HEIGHT, 480); // 카메라 영상 세로 크기 설정

        *cameraMatrix = (cv::Mat1d(3, 3) << 652.551, 0, 333.847, 0, 641.968, 234.218, 0, 0, 1);
        *distCoeffs = (cv::Mat1d(1, 4) << -0.444277, 0.253481, 0.001623, 0.000861);
        // 카메라 캘리브레이션을 위한 데이터
        break;
    }
    default:
        return false;
    }
    
    return true;
}
