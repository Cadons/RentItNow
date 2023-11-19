#ifndef USERRENTFORM_H
#define USERRENTFORM_H

#include "model/user.h"
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
 void updateUsers();
private slots:
    void on_whoAmI_comboBox_currentIndexChanged(int index);

    void on_whoAmI_comboBox_activated(int index);

    void on_search_pushButton_clicked();

private:
    Ui::UserRentForm *ui;
    User* selectedUser;
    std::string bestLp;
    float bestPrice;

};

#endif // USERRENTFORM_H
