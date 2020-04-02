#ifndef SETTING_CONTROL_H
#define SETTING_CONTROL_H

enum cam_modes
{
    NO_CAM_MODE = 0,
    qVGA_MODE = 320240,
    VGA_MODE = 640480
};

typedef struct _setting_data
{
    int detect_delay;
    int min_size_to_detect;
    int brightness;
    int saturation;
    cam_modes cam_mode;

    _setting_data() :
        detect_delay(100),
        min_size_to_detect(10000),
        brightness(0),
        saturation(160),
        cam_mode(VGA_MODE) {}

    _setting_data(const _setting_data& tmp) :
        detect_delay(tmp.detect_delay),
        min_size_to_detect(tmp.min_size_to_detect),
        brightness(tmp.brightness),
        saturation(tmp.saturation),
        cam_mode(tmp.cam_mode) {}

} setting_data;


#endif // SETTING_CONTROL_H
