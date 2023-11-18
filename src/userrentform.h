#ifndef USERRENTFORM_H
#define USERRENTFORM_H

#include <QWidget>

namespace Ui {
class UserRentForm;
}

class UserRentForm : public QWidget
{
    Q_OBJECT

public:
    explicit UserRentForm(QWidget *parent = nullptr);
    ~UserRentForm();

private:
    Ui::UserRentForm *ui;
};

#endif // USERRENTFORM_H
