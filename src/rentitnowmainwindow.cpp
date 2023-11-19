#include "rentitnowmainwindow.h"
#include "./ui_rentitnowmainwindow.h"
#include "carmanager.h"
#include "carserviceworker.h"
#include "qthread.h"
#include "userrentform.h"

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
    on_actionI_m_User_triggered();
    QThread* thread = new QThread();
    CarServiceWorker* carService = new CarServiceWorker();
    carService->moveToThread(thread);
    connect( carService, &CarServiceWorker::error, this, [](){});
    connect( thread, &QThread::started, carService, &CarServiceWorker::process);
    connect( carService, &CarServiceWorker::finished, thread, &QThread::quit);
    connect( carService, &CarServiceWorker::finished, carService, &CarServiceWorker::deleteLater);
    connect( thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();

}

RentItNowMainWindow::~RentItNowMainWindow()
{
    delete ui;
}


void RentItNowMainWindow::on_actionCar_Managment_triggered()
{
    if(isBoss)
    {
        if(userManager!=nullptr)
            userManager->hide();
        if(carManager==nullptr)
        {
            this->carManager=std::make_unique<CarManager>(this);
            ui->verticalLayout->addWidget(carManager.get());
        }
        carManager->show();

    }


}

void RentItNowMainWindow::on_actionUserManagment_triggered()
{
    if(isBoss)
    {
        if(carManager!=nullptr)
            carManager->hide();
        if(userManager==nullptr)
        {
            this->userManager=std::make_unique<UserManager>(this);
            ui->verticalLayout->addWidget(userManager.get());
        }
        userManager->show();

    }

}
void RentItNowMainWindow::on_actionI_m_Boss_triggered()
{
    isBoss=true;
   if(rentForm!=nullptr)
        rentForm->hide();
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
    if(userManager!=nullptr)
    {
        userManager->hide();


    }

    if(rentForm==nullptr)
    {
        this->rentForm=std::make_unique<UserRentForm>(this);

        ui->verticalLayout->addWidget(this->rentForm.get());
    }
    rentForm->updateUsers();
    rentForm->show();
    ui->actionCar_Managment->setDisabled(true);
    ui->actionUserManagment->setDisabled(true);
    ui->menuI_am->setTitle(QString("I am a User"));
}




