#include "usermanager.h"
#include "ui_usermanager.h"
#include "service/usermanagementservice.h"
Usermanager::Usermanager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Usermanager),
    userManager(UserManagementService::getInstance())
{
    ui->setupUi(this);

}

Usermanager::~Usermanager()
{
    delete ui;
}
