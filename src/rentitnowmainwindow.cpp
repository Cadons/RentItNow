#include "rentitnowmainwindow.h"
#include "./ui_rentitnowmainwindow.h"
#include "carmanager.h"

RentItNowMainWindow::RentItNowMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RentItNowMainWindow)
{
    ui->setupUi(this);
}

RentItNowMainWindow::~RentItNowMainWindow()
{
    delete ui;
}


void RentItNowMainWindow::on_actionCar_Managment_triggered()
{
    CarManager* carManager=new CarManager(this);
    ui->verticalLayout->addWidget(carManager);
}

