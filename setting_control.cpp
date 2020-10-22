#include "setting_control.h"

void string_to_set_ptr(
        std::map<std::string, void*>* map,
        setting_data* set
)
{
    map->insert(
        std::make_pair("portName",&set->portName));
    map->insert(
        std::make_pair("cam_number",&set->cam_number));
    map->insert(
        std::make_pair("detect_delay",&set->detect_delay));
    map->insert(
        std::make_pair("min_size_to_detect",&set->min_size_to_detect));
    map->insert(
        std::make_pair("px_to_mm",&set->px_to_mm_ratio));
    map->insert(
        std::make_pair("smoothing",&set->smoothing));
    map->insert(
        std::make_pair("brightness",&set->brightness));
    map->insert(
        std::make_pair("saturation",&set->saturation));
    map->insert(
                std::make_pair("rating",&set->ratings));
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

        if(string_to_value.count(file_data_name))
        {
            if(file_data_name == "rating")
            {
                setting_file>>file_value;
                ((QList<int>*)string_to_value[file_data_name])->append(file_value);
            }
            else if(file_data_name == "portName")
            {
                std::string portName;
                setting_file>>portName;
                *(QString*)string_to_value[file_data_name] = QString::fromStdString(portName);
            }
            else if(file_data_name == "px_to_mm")
            {
                float px_to_mm;
                setting_file>>px_to_mm;
                *(float*)string_to_value[file_data_name] = px_to_mm;
            }
            else
            {
                setting_file>>file_value;
                if(file_data_name == "smoothing")
                {
                    if(file_value % 2 == 0) throw "설정값이 옳지 않습니다";
                }

                *(int*)string_to_value[file_data_name] = file_value;
            }
        }
    }

    return set;
}

void make_setting_file(const char* path, setting_data* set)
{
    std::ofstream setting_file(path);

    std::map<std::string, void*> string_to_value;

    string_to_set_ptr(&string_to_value, set);

    for(auto data = string_to_value.begin();
        data!=string_to_value.end();
        data++)
    {
        if(data->first == "rating")
        {
            foreach(auto rating, *(QList<int>*)data->second)
            {
                setting_file << data->first << " "
                             << rating << std::endl;
            }
        }

        else if(data->first == "portName")
        {
            setting_file << data->first << " "
                         << (*(QString*)data->second).toStdString() << std::endl;
        }

        else if(data->first == "px_to_mm")
        {
            setting_file << data->first << " "
                         << (float*)data->second << std::endl;
        }

        else
        {
            setting_file << data->first << " "
                         << *(int*)data->second << std::endl;
        }
    }
}
