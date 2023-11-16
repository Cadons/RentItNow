#include "carmanager.h"
#include "model/deluxecar.h"
#include "model/ecocar.h"
#include "model/midclasscar.h"
#include "tables/carmodel.h"
#include "ui_carmanager.h"
#include "service/carmanagmentservice.h"
#include <QMessageBox>
CarManager::CarManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarManager),
    carManager(CarManagmentService::getInstance())

{
    ui->setupUi(this);

}

CarManager::~CarManager()
{
    delete ui;
}


void CarManager::on_addCar_pushButton_clicked()
{
    QString carName=this->ui->name_lineEdit->text();
    QString carBrand=this->ui->brand_lineEdit->text();
    QString lp=this->ui->lp_lineEdit->text();
    if(carName.isEmpty()||carBrand.isEmpty()||lp.isEmpty())
    {

        QMessageBox::warning(this, "RentItNow",
                              "Compile all fields",
                              QMessageBox::Ok,
                              QMessageBox::Ok);
    }else{
        bool added=false;
        Car* newCar;
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


}
void CarManager::cleanForm(){
    ui->name_lineEdit->clear();
    ui->brand_lineEdit->clear();
    ui->lp_lineEdit->clear();
    ui->carType_comboBox->setCurrentIndex(0);
}

void CarManager::on_reset_pushButton_clicked()
{
    cleanForm();
}



void CarManager::on_tabWidget_currentChanged(int index)
{
    if(index==1)
    {
        ui->carsTable->setModel(dynamic_cast<QAbstractTableModel*>(new CarModel(carManager.getCars(),this)));
        ui->carsTable->show();
    }else{
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
    }

}


void CarManager::on_carsTable_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        ui->edit_pushButton->setEnabled(true);
        ui->delete_pushButton->setEnabled(true);
        this->selectedCar=(new CarModel(carManager.getCars(),this))->getCar(index.row());
    }else{
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
    }

}


void CarManager::on_edit_pushButton_clicked()
{
    ui->name_lineEdit->setText(QString::fromStdString(selectedCar->getName()));
    ui->brand_lineEdit->setText(QString::fromStdString(selectedCar->getBrand()));

    ui->lp_lineEdit->setText(QString::fromStdString(selectedCar->getLicensePlate()));
    ui->carType_comboBox->setCurrentText(QString::fromStdString(selectedCar->getLicensePlate()));//can't be edit after the add
    ui->carType_comboBox->setEnabled(false);
    ui->reset_pushButton->setEnabled(false);
    ui->addCar_pushButton->setText("Update");

    ui->tabWidget->setCurrentIndex(0);

}

