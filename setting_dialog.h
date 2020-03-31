#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>

namespace Ui {
class setting_dialog;
}

class setting_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit setting_dialog(QWidget *parent = nullptr);
    ~setting_dialog();

private slots:

private:
    Ui::setting_dialog *ui;
};

#endif // SETTING_DIALOG_H
