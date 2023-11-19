#include "carserviceworker.h"
#include "service/carmanagementservice.h"
#include <QThread>
CarServiceWorker::CarServiceWorker()
    : QObject{}
{

}

CarServiceWorker::~CarServiceWorker()
{

}

void CarServiceWorker::process()
{
    while(true)
    {
        CarManagementService::getInstance().updateMaintenanceStatus();
        QThread::sleep(3);
        qDebug("Car service tick");
    }
}
