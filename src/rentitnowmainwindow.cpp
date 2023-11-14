#include "rentitnowmainwindow.h"
#include "./ui_rentitnowmainwindow.h"

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

