#ifndef EEL_DETECT_H
#define EEL_DETECT_H

#include <opencv2/opencv.hpp>

typedef struct _eel_data {
    bool success;
    float length;

    _eel_data(bool _success) : success(_success), length(0) {}

    _eel_data(bool _success, float _length) : success(_success), length(_length) {}


} eel_data;

#endif // EEL_DETECT_H
