#ifndef THREADWORKER_H
#define THREADWORKER_H


#include "model/location.h"
#include "qobject.h"
class ThreadWorker : public QObject
{
    Q_OBJECT
public:
    ThreadWorker(std::string lp,std::string dl, std::list<Location> path);
    ~ThreadWorker();
private:
    std::string lp;
       std::string dl;
    std::list<Location> path;
signals:
    void finished();
    void error(QString err);
public slots:
    void process();
};

#endif // THREADWORKER_H
