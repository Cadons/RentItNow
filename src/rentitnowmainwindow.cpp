#include "rentitnowmainwindow.h"
#include "./ui_rentitnowmainwindow.h"
#include "carmanager.h"
RentItNowMainWindow::RentItNowMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RentItNowMainWindow)
{
    ui->setupUi(this);
    carManager=nullptr;
    isBoss=false;
    ui->menuI_am->setTitle(QString("I am a User"));
    ui->actionCar_Managment->setDisabled(true);
    ui->actionUserManagment->setDisabled(true);
}

RentItNowMainWindow::~RentItNowMainWindow()
{
    delete ui;
    delete carManager;
}


void RentItNowMainWindow::on_actionCar_Managment_triggered()
{
    if(isBoss)
    {
        if(carManager==nullptr)
        {
            CarManager* carManager=new CarManager(this);
            ui->verticalLayout->addWidget(carManager);
            this->carManager=carManager;
        }
    }


}


void RentItNowMainWindow::on_actionI_m_Boss_triggered()
{
    isBoss=true;

    ui->actionCar_Managment->setDisabled(false);
    ui->actionUserManagment->setDisabled(false);

    ui->menuI_am->setTitle(QString("I am the Boss"));

}


void RentItNowMainWindow::on_actionI_m_User_triggered()
{
    isBoss=false;
    if(carManager!=nullptr)
    {
        carManager->hide();

    }
    ui->actionCar_Managment->setDisabled(true);
    ui->actionUserManagment->setDisabled(true);
    ui->menuI_am->setTitle(QString("I am a User"));
}

