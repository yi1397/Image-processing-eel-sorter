#include "eel_detect.h"

float px_to_cm_ratio = 1; // 1cm가 몇 픽셀인지 저장하는 변수


template<typename T_P>
inline auto calc_dist(T_P& A, T_P& B) -> decltype (T_P().x + T_P().y)
// cv::Point 구조체를 파라미터로 받아서 두 cv::Point의 거리를 측정하는 함수
{
    auto x_dist = A.x - B.x; // A와 B의 x방향 거리차이
    auto y_dist = A.y - B.y; // A와 B의 y방향 거리차이

    return x_dist * x_dist + y_dist * y_dist; // A와 B의 거리차이의 제곱의 합을 return해줌
}


bool detect_eel(
    cv::Mat& input,
    setting_data* set
)
{
    static cv::Mat hsv_img; // hsv형식의 색상 데이터가 저장될 cv::Mat 변수

    cv::cvtColor(input, hsv_img, cv::COLOR_BGR2HSV);
    // hsv_img변수에 cam_img의 데이터를 hsv형식으로 변환해서 저장

    static cv::Mat channels[3]; // h, s, v 데이터를 각각 저장할 vector<Mat>선언
    cv::split(hsv_img, channels); // channels에 h, s, v 데이터를 각각 저장함

    uchar* data_s = (uchar*)channels[1].data; // channels[1] (채도 데이터)에 접근하기 위한 포인터
    uchar* data_v = (uchar*)channels[2].data; // channels[2] (밝기 데이터)에 접근하기 위한 포인터
    int data_len = input.rows * input.cols; // 입력받은 이미지의 크기

    int cnt=0;

    for (int i = data_len; i--;)
        // hsv데이터를 읽고 이미지에서 장어와 비슷한 색상영역을 찾아내는 for문
    {
        data_s[i] < set->saturation || data_v[i] < set->brightness ? cnt++ : 0;
    }
    if(set->min_size_to_detect < cnt) return true;
    //cv::putText(input, "NO detect", cv::Point(50,50), 1, 2, cv::Scalar(255, 0, 0));
    return false;
}


eel_data measure_eel_length(
    cv::Mat& input, // 입력된 이미지
    setting_data* set
)
// 장어의 길이를 감지하고 결과 이미지를 출력해주는 함수
{
    bool success = false;

    clock_t begin_t, end_t;

    begin_t = clock();

    float length = 0; // 장어의 길이가 기억될 변수

    float detect_area = 0; // 장어의 면적이 기억될 변수

    cv::Mat threshold_img(input.size(), CV_8U); // input이미지와 같은크기의 비어있는 cv::Mat 변수

    cv::Mat detect(input.size(), CV_8UC3); // input이미지와 같은크기의 비어있는 cv::Mat 변수

    detect = cv::Scalar(0, 0, 0); // detect를 검은색 이미지로 초기화

    static cv::Mat hsv_img; // hsv형식의 색상 데이터가 저장될 cv::Mat 변수

    cv::medianBlur(input, input, 3);

    cv::cvtColor(input, hsv_img, cv::COLOR_BGR2HSV);
    // hsv_img변수에 cam_img의 데이터를 hsv형식으로 변환해서 저장

    static cv::Mat channels[3]; // h, s, v 데이터를 각각 저장할 vector<Mat>선언
    cv::split(hsv_img, channels); // channels에 h, s, v 데이터를 각각 저장함


    uchar* fixed_data = (uchar*)threshold_img.data; // threshold_img에 접근하기 위한 포인터
    uchar* data_s = (uchar*)channels[1].data; // channels[1] (채도 데이터)에 접근하기 위한 포인터
    uchar* data_v = (uchar*)channels[2].data; // channels[2] (밝기 데이터)에 접근하기 위한 포인터
    int data_len = input.rows * input.cols; // 입력받은 이미지의 크기

    for (int i = data_len; i--;)
        // hsv데이터를 읽고 이미지에서 장어와 비슷한 색상영역을 찾아내는 for문
    {
        fixed_data[i] = data_s[i] < set->saturation || data_v[i] < set->brightness ? 255u : 0u;
        //장어와 비슷한 색상 영역은 255u, 그렇지 않은 영역은 0u으로 저장
    }

    std::vector<std::vector<cv::Point>> contours; // threshold_img의 윤곽선을 저장할 벡터
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(threshold_img, contours, hierarchy,
        cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    // threshold의 윤곽선을 contours에 저장함

    int size = contours.size(); // contours에 저장된 contour의 갯수를 기억하는 변수
    int max_contour = 0;

    if (size) // contour가 없으면 실행하지 않음
    {
        success = true;

        for (int i = 0; i < size; i++) // contours에서 가장 면적이 큰 contour를 찾는 for문
        {
            double area = cv::contourArea(contours[i]); // 현재 contour의 면적

            if (detect_area < area) // 현재 contour의 면적이 max_Area보다크면
            {
                detect_area = area; // max_Area에 현재 contour의 면적을 저장
                max_contour = i; //가장 면적이 큰 contour의 번호를 기억
            }
        }

        float min_dist = 10e+10; // 장어의 두께를 기억하는 변수

        cv::Point minA, minB; // contour의 cv::Point를 저장할 변수

        int contour_count = (int)contours[max_contour].size(); // contour의 꼭지점의 개수

        for (int i = contour_count >> 1; i; --i) // 가장 면적이 큰 contour의 1번부터 절반까지 반복
            // i는 가장큰 contour의 0번부터 절반까지 반복
        {
            for (int j = -(contour_count >> 3) + 1;
                j < (contour_count >> 3);
                ++j)
                // j는 contour크기의 -1/8부터 가장큰 contour크기의 1/8 까지 증가
            {
                int k = (i + (contour_count >> 1) + j);
                k = k < contour_count ? k : k - contour_count;
                // k는 i의 반대지점에서 ± contour크기의 1/8 사이

                auto dist = calc_dist(contours[max_contour][i], contours[max_contour][k]);
                // 가장큰 contour의 i번째와 k번째 사이의 거리를 기억하는 변수

                if (dist < min_dist) // dist가 최단거리이면
                {
                    min_dist = dist; // dist를 저장

                    minA = contours[max_contour][i];
                    minB = contours[max_contour][k];
                    // i번째 꼭지점과 k번째 꼭지점의 위치를 기억
                }
            }
        }
        min_dist = sqrt(min_dist);
        // 장어의 두께를 계산

        cv::line(input, minA, minB, cv::Scalar(0, 255, 0), 2);
        // 결과 이미지에 minA와 minB 사이를 표시해줌

        length = round(detect_area / min_dist / px_to_cm_ratio);
        // 길이를 계산함

    }


    cv::drawContours(input, contours, max_contour,
        cv::Scalar(255, 0, 0), 2, 8, hierarchy, 0, cv::Point());
    // 결과 이미지에 장어 윤곽선을 표시해줌

    float area = round(detect_area / px_to_cm_ratio / px_to_cm_ratio);

    end_t = clock();

    return eel_data(true, length, area, end_t - begin_t);
}
