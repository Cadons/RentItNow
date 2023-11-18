#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "service/IUserManager.h"
#include "userform.h"
#include <QWidget>

namespace Ui {
class UserManager;
}

class UserManager : public QWidget
{
    Q_OBJECT

public:
    explicit UserManager(QWidget *parent = nullptr);
    ~UserManager();

private slots:
    void on_UserManagment_currentChanged(int index);

    void on_edit_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void on_usersTable_clicked(const QModelIndex &index);

private:
    Ui::UserManager *ui;

    IUserManager& userManager;
    std::unique_ptr<UserForm> newForm;
    std::unique_ptr<UserForm> editForm;
    User* selecteUser;
    void updateTable();


};

#endif // USERMANAGER_H
