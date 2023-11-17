#ifndef USERFORM_H
#define USERFORM_H

#include "model/car.h"
#include "model/user.h"
#include "qtabwidget.h"
#include "service/IUserManager.h"
#include <QWidget>

namespace Ui {
class UserForm;
}

class UserForm : public QWidget
{
    Q_OBJECT

public:
    explicit UserForm(QWidget *parent = nullptr);
    UserForm(User* user, QTabWidget* tabMenu,QWidget *parent = nullptr);
    ~UserForm();

private slots:
    void on_reset_pushButton_clicked();


    void on_addUser_pushButton_clicked();

private:
    Ui::UserForm *ui;
    void cleanForm();
    bool editMode=false;
    QTabWidget* tabMenu;
    User* userToEdit;
    IUserManager& userManager;
    void back();
};

#endif // USERFORM_H
