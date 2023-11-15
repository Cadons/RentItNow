#include "carmanager.h"
#include "ui_carmanager.h"

CarManager::CarManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarManager)
{
    ui->setupUi(this);
}

CarManager::~CarManager()
{
    delete ui;
}

void CarManager::on_resetCar_pushButton_clicked()
{
    ui->name_lineEdit->clear();
    ui->brand_lineEdit->clear();
    ui->lp_lineEdit->clear();
    ui->carType_comboBox->setCurrentIndex(0);
}
void CarManager::on_pushButton_2_clicked()
{
    ui->name_lineEdit->clear();
    ui->brand_lineEdit->clear();
    ui->lp_lineEdit->clear();
    ui->carType_comboBox->setCurrentIndex(0);
}

void CarManager::on_addCar_pushButton_clicked()
{

}


void CarManager::on_reset_pushButton_clicked()
{
    ui->name_lineEdit->clear();
    ui->brand_lineEdit->clear();
    ui->lp_lineEdit->clear();
    ui->carType_comboBox->setCurrentIndex(0);
}


