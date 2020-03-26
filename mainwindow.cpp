#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camera_control.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool success;
    success = camera_init(&main_cap, cameraMatrix, distCoeffs, VGA_MODE);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}
