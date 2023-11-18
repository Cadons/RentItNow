#include "userrentform.h"
#include "model/circle.h"
#include "service/rentingservice.h"
#include "ui_userrentform.h"
#include "service/usermanagementservice.h"
UserRentForm::UserRentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserRentForm)
{
    ui->setupUi(this);
    updateUsers();
    // Create a QMap for associations
    QMap<QString, int> circleAssociations;

    circleAssociations["Outer Circle"] = 0;
    circleAssociations["Middle Circle"] = 1;
    circleAssociations["Inner Circle"] = 2;

    // Populate the QComboBox using the QMap
    ui->from_comboBox->addItems(circleAssociations.keys());
    ui->to_comboBox->addItems(circleAssociations.keys());
}

UserRentForm::~UserRentForm()
{
    delete ui;
}

void UserRentForm::on_whoAmI_comboBox_currentIndexChanged(int index)
{
    QVariant userData = ui->whoAmI_comboBox->currentData();

        std::string drivingLicense = userData.toString().toStdString();
        qDebug() << drivingLicense;

        // Now you can use drivingLicense in your code
        selectedUser = UserManagementService::getInstance().getUser(drivingLicense);
        if (selectedUser != nullptr) {
            ui->Addresss_label->setText(QString::fromStdString(selectedUser->getAddress()));
            ui->CC_label->setText(QString::fromStdString(selectedUser->getCreditCard()));
            ui->DL_label->setText(QString::fromStdString(selectedUser->getDrivingLicense()));
        }else{
            ui->Addresss_label->setText(QString::fromStdString("..."));
            ui->CC_label->setText(QString::fromStdString("..."));
            ui->DL_label->setText(QString::fromStdString("..."));
        }


}


void UserRentForm::on_whoAmI_comboBox_activated(int index)
{

}

void UserRentForm::updateUsers()
{
              ui->whoAmI_comboBox->clear();
        ui->whoAmI_comboBox->addItem(QString("Select user"));

        for(const auto& it: UserManagementService::getInstance().getUsers())
        {
            ui->whoAmI_comboBox->addItem(QString(QString::fromStdString(it.second->getName()+" "+it.second->getSurname())),QVariant::fromValue(QString::fromStdString(it.second->getDrivingLicense())));
        }

}


void UserRentForm::on_search_pushButton_clicked()
{
        if(ui->passagers_spinBox->value()>0&&selectedUser!=nullptr)
        {
            int passegers=ui->passagers_spinBox->value();
            Location from;
            Location to;
            CarTypeName type;
            switch (ui->from_comboBox->currentData().toInt()) {
            case 0:
                from.setPosition(SimpleTown::getInstance().getOuter());
                break;
            case 1:
                from.setPosition(SimpleTown::getInstance().getOuter()->getChild());

                break;
            case 2:
                from.setPosition(SimpleTown::getInstance().getInner());

                break;
            default:
                break;
            }
            switch (ui->to_comboBox->currentData().toInt()) {
            case 0:
                to.setPosition(SimpleTown::getInstance().getOuter());
                break;
            case 1:
                to.setPosition(SimpleTown::getInstance().getOuter()->getChild());

                break;
            case 2:
                to.setPosition(SimpleTown::getInstance().getInner());

                break;
            default:
                break;
            }
            switch (ui->carType_comboBox->currentIndex()) {
            case 0:
                type=ECO;
                break;
            case 1:
                type=MID_CLASS;
                break;
            case 2:
                type=DELUXE;
                break;
            default:
                break;
            }

          //  auto result= RentingService::getInstance().requestRent(selectedUser->getDrivingLicense(),passegers,type,from,to);

        }
        }

