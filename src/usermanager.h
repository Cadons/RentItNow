#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "service/IUserManager.h"
#include "userform.h"
#include <QWidget>

namespace Ui {
class Usermanager;
}

class Usermanager : public QWidget
{
    Q_OBJECT

public:
    explicit Usermanager(QWidget *parent = nullptr);
    ~Usermanager();

private:
    Ui::Usermanager *ui;

    IUserManager& userManager;
    UserForm* newForm;
    UserForm* editForm;
    User* selecteUser;
    void updateTable();


};

#endif // USERMANAGER_H
