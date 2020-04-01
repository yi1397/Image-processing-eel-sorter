#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>

namespace Ui {
class setting_dialog;
}

class setting_dialog : public QDialog
{
    Q_OBJECT

signals:
    void send_setting(int value);

public:
    explicit setting_dialog(QWidget *parent = nullptr);
    ~setting_dialog();

private slots:


    void on_confirm_Button_clicked();

private:
    Ui::setting_dialog *ui;
};

#endif // SETTING_DIALOG_H
