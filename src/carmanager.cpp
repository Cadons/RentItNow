#include "carmanager.h"

#include "carform.h"
#include "tables/carmodel.h"
#include "ui_carmanager.h"
#include "service/carmanagementservice.h"
#include <QMessageBox>

CarManager::CarManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarManager),
    carManager(CarManagementService::getInstance())

{
    ui->setupUi(this);
    newForm=std::make_unique<CarForm>(this);
    ui->CarManagment->setCurrentIndex(0);
    ui->CarManagment->addTab(newForm.get(),"Add new car");

    updateTable();
}

CarManager::~CarManager()
{
    delete ui;

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
    if(this->selectedCar!=nullptr){

        if( ui->CarManagment->count()==2)
        {

            CarForm* editCarForm=new CarForm(this->selectedCar, ui->CarManagment,this);
            ui->CarManagment->addTab(editCarForm,QString("Edit Car"));
            ui->CarManagment->setCurrentIndex(2);

            this->editForm=std::make_unique<CarForm>(editCarForm);
        }else{
            QMessageBox::warning(this, "RentItNow",
                                 "You are editing an other car, close the tab and retry!",
                                 QMessageBox::Ok
                                 );
        }
    }


}


void CarManager::on_CarManagment_currentChanged(int index)
{
    if(index==0)
    {
      updateTable();
    }else{
        ui->edit_pushButton->setEnabled(false);
        ui->delete_pushButton->setEnabled(false);
    }
}


void CarManager::on_delete_pushButton_clicked()
{
    if( ui->CarManagment->count()==2)
    {
    if(selectedCar!=nullptr)
    {
        int ret=QMessageBox::critical(this, "RentItNow",
                                        "Do you want delete this car from the database",
                                        QMessageBox::Yes|QMessageBox::No
                                        );
        if(ret==QMessageBox::Yes)
        {
           bool removed= carManager.remove(selectedCar->getLicensePlate());
            if(removed)
           {
               QMessageBox::information(this, "RentItNow",
                                        "Car deleted",
                                        QMessageBox::Ok,
                                        QMessageBox::Ok);

               ui->carsTable->clearSelection();
               on_CarManagment_currentChanged(0);
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
                         "You are editing an other car, close the tab and retry!",
                         QMessageBox::Ok
                         );
    }
}

void CarManager::updateTable()
{
    ui->carsTable->setModel(dynamic_cast<QAbstractTableModel*>(new CarModel(carManager.getCars(),this)));
    ui->carsTable->show();
}


void CarManager::on_refresh_pushButton_clicked()
{
    updateTable();
}

