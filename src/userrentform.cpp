#include "userrentform.h"
#include "ui_userrentform.h"

UserRentForm::UserRentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserRentForm)
{
    ui->setupUi(this);
}

UserRentForm::~UserRentForm()
{
    delete ui;
}
