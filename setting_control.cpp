#include "setting_control.h"

#include <QMessageBox>
#include <fstream>

void make_setting_file()
{

}

setting_data get_setting_file(const char* path)
{
    setting_data set;
    std::ifstream setting_file(path);
    if(!setting_file.is_open())
    {
        QMessageBox::information(NULL, "올바르지않은 설정", "설정파일을 초기화 해야 합니다");
        make_setting_file();
        return set;
    }

    return set;
}
