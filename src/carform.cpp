#include "carform.h"
#include "carmanager.h"
#include "ui_carform.h"
#include <QMessageBox>
#include "model/deluxecar.h"
#include "model/ecocar.h"
#include "model/midclasscar.h"
#include "service/carmanagementservice.h"

CarForm::CarForm(Car* car,QTabWidget* tabMenu,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarForm),
    carToEdit(car),
    tabMenu(tabMenu),
    carManager(CarManagementService::getInstance())

{
    ui->setupUi(this);
    if(car!=nullptr)
    {
        editMode=true;
        ui->name_lineEdit->setText(QString::fromStdString(car->getName()));
        ui->brand_lineEdit->setText(QString::fromStdString(car->getBrand()));
        ui->lp_lineEdit->setText(QString::fromStdString(car->getLicensePlate()));

        ui->carType_comboBox->clear();
        ui->carType_comboBox->addItem(QString::fromStdString(car->getTypeName()));
        ui->lp_lineEdit->setEnabled(false);//after registration lp can't be changed
        ui->carType_comboBox->setEnabled(false);//Same for the type
        ui->addCar_pushButton->setText("Update");
        ui->reset_pushButton->setText("Cancel");

    }

}
CarForm::CarForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarForm),
    carManager(CarManagementService::getInstance())
{
    ui->setupUi(this);
    carToEdit=nullptr;
    editMode=false;
    tabMenu=nullptr;

}
CarForm::~CarForm()
{
    delete ui;
    if(tabMenu!=nullptr)
    delete tabMenu;
    if(carToEdit!=nullptr)
        delete carToEdit;
}

void CarForm::on_addCar_pushButton_clicked()
{

    QString carName=this->ui->name_lineEdit->text();
    QString carBrand=this->ui->brand_lineEdit->text();
    QString lp=this->ui->lp_lineEdit->text();
    Car* newCar=nullptr;
    if(!editMode){


        if(carName.isEmpty()||carBrand.isEmpty()||lp.isEmpty())
        {

            QMessageBox::warning(this, "RentItNow",
                                 "Compile all fields",
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
        }else{
            bool added=false;

            switch (ui->carType_comboBox->currentIndex()) {
            case 0:
                newCar=new EcoCar(carName.toStdString(),carBrand.toStdString(), lp.toStdString());
                added=carManager.add(newCar);
                delete newCar;
                break;
            case 1:
                newCar=new MidClassCar(carName.toStdString(),carBrand.toStdString(), lp.toStdString());
                added=carManager.add(newCar);
                delete newCar;
                break;
            case 2:
                newCar=new DeluxeCar(carName.toStdString(),carBrand.toStdString(), lp.toStdString());
                added=carManager.add(newCar);
                delete newCar;
                break;

            default:
                QMessageBox::critical(this, "RentItNow",
                                      "This car type is not supported",
                                      QMessageBox::Ok,
                                      QMessageBox::Ok);
                break;
            }
            if(added)
            {
                int ret=QMessageBox::information(this, "RentItNow",
                                                   "Car registred",
                                                   QMessageBox::Ok,
                                                   QMessageBox::Ok);
                if(ret==QMessageBox::Ok)
                {
                    cleanForm();

                }
            }else{
                QMessageBox::critical(this, "RentItNow",
                                      "Car already registred",
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
            newCar=carToEdit;
            newCar->setName(carName.toStdString());
            newCar->setBrand(carBrand.toStdString());

            update=carManager.update(lp.toStdString(),newCar);

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


void CarForm::on_reset_pushButton_clicked()
{
    if(!editMode)
    {
        cleanForm();
    }else{
        back();
    }
}

void CarForm::cleanForm(){
    ui->name_lineEdit->clear();
    ui->brand_lineEdit->clear();
    ui->lp_lineEdit->clear();
    ui->carType_comboBox->setCurrentIndex(0);
}

void CarForm::back()
{
    tabMenu->setCurrentIndex(0);
    tabMenu->removeTab(2);

}
