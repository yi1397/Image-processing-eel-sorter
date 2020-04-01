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
    cam_modes cam_mode;

} setting_data;

#endif // SETTING_CONTROL_H
