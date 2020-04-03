#include "setting_control.h"


void make_setting_file()
{

}

void string_to_set_ptr(
        std::map<std::string, void*>* map,
        setting_data* set
)
{
    map->insert(
        std::make_pair("detect_delay",&set->detect_delay));
    map->insert(
        std::make_pair("min_size_to_detect",&set->min_size_to_detect));
    map->insert(
        std::make_pair("smoothing",&set->smoothing));
    map->insert(
        std::make_pair("brightness",&set->brightness));
    map->insert(
        std::make_pair("saturation",&set->saturation));
    map->insert(
        std::make_pair("cam_mode",&set->cam_mode));
}

setting_data get_setting_from_file(const char* path)
{
    setting_data set;
    std::ifstream setting_file(path);
    if(setting_file.fail())
    {
        throw "파일이 없습니다";
    }

    std::map<std::string, void*> string_to_value;

    string_to_set_ptr(&string_to_value, &set);

    while(!setting_file.eof())
    {
        std::string file_data_name;
        int file_value;

        setting_file>>file_data_name;
        setting_file>>file_value;

        if(string_to_value.count(file_data_name))
        {
            *(int*)string_to_value[file_data_name] = file_value;
        }
    }

    return set;
}
