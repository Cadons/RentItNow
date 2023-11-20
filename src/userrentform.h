#ifndef USERRENTFORM_H
#define USERRENTFORM_H

#include "model/location.h"
#include "model/user.h"
#include "qlcdnumber.h"
#include <QWidget>

namespace Ui {
class UserRentForm;
}

class UserRentForm : public QWidget
{
    Q_OBJECT

public:
    explicit UserRentForm(QLCDNumber *bankValueLCD=nullptr,QWidget *parent = nullptr);
    ~UserRentForm();
 void updateUsers();
private slots:
    void on_whoAmI_comboBox_currentIndexChanged(int index);

    void on_whoAmI_comboBox_activated(int index);

    void on_search_pushButton_clicked();

    void on_rent_pushButton_clicked();
public slots:
    void rent_car_simulation(std::string lp);
signals:
    void releaseCar();

private:
    Ui::UserRentForm *ui;
    User* selectedUser;
    std::string bestLp;
    float bestPrice;
    std::list<Location> path;
    QLCDNumber* bankValueLCD;
};

#endif // USERRENTFORM_H
