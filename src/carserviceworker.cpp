#include "carserviceworker.h"
#include "service/carmanagementservice.h"
#include <QThread>
bool CarServiceWorker::run = true;  // Definition of the static member variable

CarServiceWorker::CarServiceWorker(QLCDNumber* time)
    : QObject{}, lcd(time)
{
}

CarServiceWorker::~CarServiceWorker()
{

}

void CarServiceWorker::process()
{
    while(CarServiceWorker::run)
    {
        CarManagementService::getInstance().updateMaintenanceStatus();
        QThread::sleep(1);
        if(lcd!=nullptr)
        {
            counter=counter%24;
            lcd->display(++counter);
        }
        //qDebug("Car service tick");
    }
    emit finished();
}
