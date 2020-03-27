#ifndef EEL_DETECT_H
#define EEL_DETECT_H

#include <opencv2/opencv.hpp>

typedef struct _eel_data {
    bool success;
    float length;

    _eel_data(bool _success) : success(_success), length(0) {}

    _eel_data(bool _success, float _length) : success(_success), length(_length) {}


} eel_data;

inline int calc_dist(cv::Point& A, cv::Point& B);
// cv::Point 구조체를 파라미터로 받아서 두 cv::Point의 거리를 측정하는 함수

#endif // EEL_DETECT_H
