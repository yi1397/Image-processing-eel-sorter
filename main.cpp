#include "mainwindow.h"
#include "camera_control.h"

#include <QApplication>

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
