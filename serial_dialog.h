#ifndef SERIAL_DIALOG_H
#define SERIAL_DIALOG_H

#include <QDialog>

namespace Ui {
class serial_Dialog;
}

class serial_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit serial_Dialog(QWidget *parent = nullptr);
    ~serial_Dialog();

private:
    Ui::serial_Dialog *ui;
};

#endif // SERIAL_DIALOG_H
