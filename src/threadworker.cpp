#include "threadworker.h"
#include "qthread.h"
#include "service/carmanagementservice.h"
#include "service/rentingservice.h"




ThreadWorker::ThreadWorker(std::string lp,std::string dl, std::list<Location> path):lp(lp),dl(dl), path(path)
{

}

ThreadWorker::~ThreadWorker()
{

}

void ThreadWorker::process()
{
    // allocate resources using new here
    qDebug("Getting the car");
       QThread::sleep(10);
    for(auto& loc : path )
       {
           CarManagementService::getInstance().moveCar(lp,loc);

       }
    RentingService::getInstance().release(lp,dl);
    qDebug("Releasing the car");
    emit finished();
}
