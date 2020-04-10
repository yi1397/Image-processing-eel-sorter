#ifndef SETTING_CONTROL_H
#define SETTING_CONTROL_H

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <map>
#include <QList>


enum cam_modes
{
    NO_CAM_MODE = 0,
    qVGA_MODE = 320240,
    VGA_MODE = 640480
};

typedef struct _setting_data
{
    int cam_number;
    int detect_delay;
    int min_size_to_detect;
    int smoothing;
    int brightness;
    int saturation;
    QList<int> ratings;
    cam_modes cam_mode;


    _setting_data() :
        cam_number(0),
        detect_delay(100),
        min_size_to_detect(10000),
        smoothing(3),
        brightness(0),
        saturation(160),
        cam_mode(VGA_MODE) {}

    _setting_data(const _setting_data& tmp) :
        cam_number(tmp.cam_number),
        detect_delay(tmp.detect_delay),
        min_size_to_detect(tmp.min_size_to_detect),
        smoothing(tmp.smoothing),
        brightness(tmp.brightness),
        saturation(tmp.saturation),
        ratings(tmp.ratings),
        cam_mode(tmp.cam_mode) {}

} setting_data;

void string_to_set_ptr(
    std::map<std::string, void*>* map,
    setting_data* set
);

void make_setting_file();

setting_data get_setting_from_file(const char* path);

void make_setting_file(const char* path, setting_data* set);

#endif // SETTING_CONTROL_H
