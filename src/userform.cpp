#include "userform.h"
#include "ui_userform.h"
#include "service/usermanagementservice.h"
#include <QMessageBox>
UserForm::UserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserForm),
    userManager(UserManagementService::getInstance())
{
    ui->setupUi(this);
    editMode=false;
    userToEdit=nullptr;
}

UserForm::UserForm(User *user, QTabWidget *tabMenu, QWidget *parent)  :  QWidget(parent),
    ui(new Ui::UserForm),
    userManager(UserManagementService::getInstance())

{
    ui->setupUi(this);
    if(user!=nullptr)
    {
        editMode=true;
        ui->name_lineEdit->setText(QString::fromStdString(user->getName()));
        ui->surname_lineEdit->setText(QString::fromStdString(user->getSurname()));
        ui->address_lineEdit->setText(QString::fromStdString(user->getAddress()));
        ui->credit_card_lineEdit->setText(QString::fromStdString(user->getCreditCard()));
        ui->driving_license_lineEdit->setText(QString::fromStdString(user->getDrivingLicense()));
        ui->addUser_pushButton->setText("Update");
        ui->reset_pushButton->setText("Cancel");
    }
}

UserForm::~UserForm()
{
    delete ui;
}

void UserForm::on_reset_pushButton_clicked()
{
    if(!editMode)
    {
        cleanForm();
    }else{
        back();
    }
}




void UserForm::on_addUser_pushButton_clicked()
{
    QString name=this->ui->name_lineEdit->text();
    QString surname=this->ui->surname_lineEdit->text();
    QString address=this->ui->address_lineEdit->text();
    QString creditCard=this->ui->credit_card_lineEdit->text();

    QString drivingLicense=this->ui->driving_license_lineEdit->text();

    User* newUser=nullptr;
    if(!editMode){


        if(name.isEmpty()||surname.isEmpty()||address.isEmpty()||creditCard.isEmpty()||drivingLicense.isEmpty())
        {

            QMessageBox::warning(this, "RentItNow",
                                 "Compile all fields",
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
        }else{
            bool added=false;


                newUser=new User(name.toStdString(),surname.toStdString(),address.toStdString(),creditCard.toStdString(),drivingLicense.toStdString());
                added=userManager.add(newUser);
                delete newUser;


            if(added)
            {
                int ret=QMessageBox::information(this, "RentItNow",
                                                   "User registred",
                                                   QMessageBox::Ok,
                                                   QMessageBox::Ok);
                if(ret==QMessageBox::Ok)
                {
                    cleanForm();
                }
            }else{
                QMessageBox::critical(this, "RentItNow",
                                      "User already registred",
                                      QMessageBox::Ok,
                                      QMessageBox::Ok);
            }

        }
    }else{

        int ret=QMessageBox::question(this, "RentItNow",
                                        "Do you want save",
                                        QMessageBox::Yes|QMessageBox::No
                                        );
        if(ret==QMessageBox::Yes)
        {
            bool update=false;
            newUser=userToEdit;
            newUser->setName(name.toStdString());
            newUser->setSurname(surname.toStdString());

            newUser->setAddress(address.toStdString());

            newUser->setCreditCard(creditCard.toStdString());
            newUser->setDrivingLicense(drivingLicense.toStdString());

            update=userManager.update(userToEdit->getDrivingLicense(),newUser);

            if(update)
            {
                ret=QMessageBox::information(this, "RentItNow",
                                               "Car modified",
                                               QMessageBox::Ok,
                                               QMessageBox::Ok);
                if(ret==QMessageBox::Ok)
                {

                    back();

                }
            }else{
                QMessageBox::critical(this, "RentItNow",
                                      "Something went wrong",
                                      QMessageBox::Ok,
                                      QMessageBox::Ok);

            }

        }
    }
}
void UserForm::cleanForm(){
    ui->name_lineEdit->clear();
    ui->surname_lineEdit->clear();
    ui->address_lineEdit->clear();
    ui->credit_card_lineEdit->clear();
    ui->driving_license_lineEdit->clear();
}

void UserForm::back()
{
    tabMenu->setCurrentIndex(0);
    tabMenu->removeTab(2);

}
