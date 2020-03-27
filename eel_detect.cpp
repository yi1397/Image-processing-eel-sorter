#include "eel_detect.h"

inline int calc_dist(cv::Point& A, cv::Point& B)
// cv::Point 구조체를 파라미터로 받아서 두 cv::Point의 거리를 측정하는 함수
{
    int x_dist = A.x - B.x; // A와 B의 x방향 거리차이
    int y_dist = A.y - B.y; // A와 B의 y방향 거리차이

    return x_dist * x_dist + y_dist * y_dist; // A와 B의 거리차이의 제곱의 합을 return해줌

}
