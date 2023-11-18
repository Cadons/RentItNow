#include "usermanager.h"
#include "qabstractitemmodel.h"
#include "tables/usermodel.h"
#include "ui_usermanager.h"
#include "service/usermanagementservice.h"
#include <QMessageBox>

UserManager::UserManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManager),
    userManager(UserManagementService::getInstance())
{
    ui->setupUi(this);
    newForm=new UserForm(this);

    ui->UserManagment->setCurrentIndex(0);
    ui->UserManagment->addTab(newForm,"Add new user");
    updateTable();

}

UserManager::~UserManager()
{
    delete ui;
}

void UserManager::on_UserManagment_currentChanged(int index)
{
    if(index==0)
    {
        updateTable();

    }else{
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
    }
}

void UserManager::updateTable()
{
    ui->usersTable->setModel(dynamic_cast<QAbstractTableModel*>(new UserModel(userManager.getUsers(),this)));
    ui->usersTable->show();
}

void UserManager::on_edit_pushButton_clicked()
{
    if(this->selecteUser!=nullptr){

        if( ui->UserManagment->count()==2)
        {

            UserForm* editCarForm=new UserForm(this->selecteUser, ui->UserManagment,this);
            ui->UserManagment->addTab(editCarForm,QString("Edit User"));
            ui->UserManagment->setCurrentIndex(2);

            editForm=editCarForm;
        }else{
            QMessageBox::warning(this, "RentItNow",
                                 "You are editing an other user, close the tab and retry!",
                                 QMessageBox::Ok
                                 );
        }
    }
}


void UserManager::on_delete_pushButton_clicked()
{
    if( ui->UserManagment->count()==2)
    {
        if(selecteUser!=nullptr)
        {
            int ret=QMessageBox::critical(this, "RentItNow",
                                            "Do you want delete this user from the database",
                                            QMessageBox::Yes|QMessageBox::No
                                            );
            if(ret==QMessageBox::Yes)
            {
                bool removed= userManager.remove(selecteUser->getDrivingLicense());
                if(removed)
                {
                    QMessageBox::information(this, "RentItNow",
                                             "User deleted",
                                             QMessageBox::Ok,
                                             QMessageBox::Ok);

                    ui->usersTable->clearSelection();
                    on_UserManagment_currentChanged(0);
                    ui->edit_pushButton->setEnabled(false);
                    ui->delete_pushButton->setEnabled(false);
                }else{
                    QMessageBox::critical(this, "RentItNow",
                                          "Something went wrong",
                                          QMessageBox::Ok,
                                          QMessageBox::Ok);

                }
            }
        }
    }else{
        QMessageBox::critical(this, "RentItNow",
                              "You are editing an other user, close the tab and retry!",
                              QMessageBox::Ok
                              );
    }
}


void UserManager::on_usersTable_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        ui->edit_pushButton->setEnabled(true);
        ui->delete_pushButton->setEnabled(true);
        this->selecteUser=(new UserModel(userManager.getUsers(),this))->getUser(index.row());
    }else{
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
    }
}

