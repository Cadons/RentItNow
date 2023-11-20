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
    qDebug("Taking the car");

    int time =  rand() % 10 + 5;
       QThread::sleep(time);
    for(auto& loc : path )
       {
           CarManagementService::getInstance().moveCar(lp,loc);

       }
    RentingService::getInstance().release(lp,dl);
    qDebug("Releasing the car");
    emit finished();
}
