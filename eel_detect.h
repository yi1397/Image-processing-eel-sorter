#ifndef EEL_DETECT_H
#define EEL_DETECT_H

#include <opencv2/opencv.hpp>

typedef struct _eel_data {
    bool success;
    float length;
    float area;
    clock_t response_time;

    _eel_data() : success(false), length(0) {}

    _eel_data(bool _success) : success(_success), length(0) {}

    _eel_data(bool _success, float _length, float _area, clock_t _response_time)
        : success(_success), length(_length), area(_area), response_time(_response_time) {}

    _eel_data(const _eel_data& tmp)
        : success(tmp.success), length(tmp.length), area(tmp.area), response_time(tmp.response_time) {}


} eel_data;

inline int calc_dist(cv::Point& A, cv::Point& B);
// cv::Point 구조체를 파라미터로 받아서 두 cv::Point의 거리를 측정하는 함수

eel_data detect_eel(
    cv::Mat& input, // 입력된 이미지
    int brightness, // 감지할 밝기 문턱값
    int saturation // 감지할 채도 문턱값
);

#endif // EEL_DETECT_H
