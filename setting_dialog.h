#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>

#include "setting_control.h"

namespace Ui {
class setting_dialog;
}

class setting_dialog : public QDialog
{
    Q_OBJECT

signals:
    void send_setting(setting_data set);

public:
    explicit setting_dialog(QWidget *parent = nullptr);
    ~setting_dialog();

private slots:
    void on_confirm_Button_clicked();

private:
    Ui::setting_dialog *ui;

    void get_setting_data(setting_data *set);
};

#endif // SETTING_DIALOG_H
