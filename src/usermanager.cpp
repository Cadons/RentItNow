#include "usermanager.h"
#include "ui_usermanager.h"

UserManager::UserManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);
}

UserManager::~UserManager()
{
    delete ui;
}
