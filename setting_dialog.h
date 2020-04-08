#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QList>

#include "setting_control.h"

namespace Ui {
class setting_dialog;
}

class setting_dialog : public QDialog
{
    Q_OBJECT

signals:
    void send_setting(setting_data set);

public slots:
    void put_data_to_lineEdit(setting_data set);

public:
    explicit setting_dialog(QWidget *parent = nullptr);
    ~setting_dialog();

private slots:

    void on_pushButton_apply_clicked();

    void on_push_Button_confirm_clicked();

    void on_pushButton_setting_load_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_make_new_settingfile_clicked();

    void on_pushButton_add_rating_clicked();

    void spinbox_changed();

    void on_pushButton_delete_rateing_clicked();

private:
    Ui::setting_dialog *ui;

    setting_data user_setting;

    void get_setting_from_input(setting_data *set);

    void apply_setting();

    void add_new_rating(int rating);

    QList<QSpinBox*> rating_SpinBox_list;
};

#endif // SETTING_DIALOG_H
