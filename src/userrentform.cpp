#include "userrentform.h"
#include "model/circle.h"
#include "service/rentingservice.h"
#include "ui_userrentform.h"
#include "service/usermanagementservice.h"
#include <QMessageBox>
UserRentForm::UserRentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserRentForm)
{
    ui->setupUi(this);
    updateUsers();


    QStringList circleNames = {"Inner Circle", "Middle Circle", "Outer Circle"};

    // Populate "from" combo box
    for (int i = 0; i < circleNames.size(); ++i) {
        ui->from_comboBox->addItem(circleNames[i], QVariant::fromValue(i));
    }

    // Populate "to" combo box
    for (int i = 0; i < circleNames.size(); ++i) {
        ui->to_comboBox->addItem(circleNames[i], QVariant::fromValue(i));
    }
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
        this->bestLp="";
        this->bestPrice=0;
        int passegers=ui->passagers_spinBox->value();
        Location from;
        Location to;
        CarTypeName type;
        qDebug()<<ui->from_comboBox->currentData().toInt();


        switch (ui->from_comboBox->currentData().toInt()) {
        case 0:
            from.setPosition(SimpleTown::getInstance().getInner());
            break;
        case 1:
            from.setPosition(SimpleTown::getInstance().getOuter()->getChild());
            break;
        case 2:
            from.setPosition(SimpleTown::getInstance().getOuter());
            break;
        default:
            break;
        }
        switch (ui->to_comboBox->currentData().toInt()) {
        case 0:
            to.setPosition(SimpleTown::getInstance().getInner());
            break;
        case 1:
            to.setPosition(SimpleTown::getInstance().getOuter()->getChild());

            break;
        case 2:
            to.setPosition(SimpleTown::getInstance().getOuter());
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

        auto result= RentingService::getInstance().requestRent(passegers,type,from,to);
        QString outputText;
        auto roundToTwoDecimals = [](float value) {
            return QString::number(std::round(value * 100.0) / 100.0, 'f', 2).toStdString();
        };

        if (result.get()->getWaitTime() == std::numeric_limits<float>::min()) {
            if (!result.get()->getResults().empty()) {
                std::string tmp="Distance(Km):" + roundToTwoDecimals(result.get()->getResults()[0].getKmDistance()) +"\nPrice:" + roundToTwoDecimals(result.get()->getResults()[0].getPrice());
                outputText = QString::fromStdString(tmp);
                this->bestLp=result.get()->getResults()[0].getCar()->getLicensePlate();
                this->bestPrice=result.get()->getResults()[0].getPrice();
            } else {
                outputText = QString::fromStdString("No cars available");
            }
        } else {
            if (result.get()->getWaitTime() != std::numeric_limits<float>::max())
                outputText = QString::fromStdString("No cars available, waiting time:" + roundToTwoDecimals(result.get()->getWaitTime()));
            else
                outputText = QString::fromStdString("There is no car that respects the requirements!");
        }
        ui->output->setText(outputText);


    }else{
        if(ui->passagers_spinBox->value()==0)
        {
            QMessageBox::critical(this, "RentItNow",
                                  "Passegers must be greater of 0",
                                  QMessageBox::Ok,
                                  QMessageBox::Ok);
        }
        if(selectedUser==nullptr)
            QMessageBox::critical(this, "RentItNow",
                                  "Select a user!",
                                  QMessageBox::Ok,
                                  QMessageBox::Ok);
    }
}

