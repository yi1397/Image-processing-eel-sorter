#ifndef EEL_DETECT_H
#define EEL_DETECT_H

#include <opencv2/opencv.hpp>

float px_to_cm_ratio = 1; // 1cm가 몇 픽셀인지 저장하는 변수

typedef struct _eel_data {
    bool success;
    float length;

    _eel_data(bool _success) : success(_success), length(0) {}

    _eel_data(bool _success, float _length) : success(_success), length(_length) {}


} eel_data;

inline int calc_dist(cv::Point& A, cv::Point& B);
// cv::Point 구조체를 파라미터로 받아서 두 cv::Point의 거리를 측정하는 함수

eel_data detect_eel(
    cv::Mat& input, // 입력된 이미지
    int brightness, // 감지할 밝기 문턱값
    int saturation // 감지할 채도 문턱값
    //Histogram1D& h // Histogram을 이용한 장어 감지를 위한 클래스(아직 기능을 추가하지 않음)
);

#endif // EEL_DETECT_H
