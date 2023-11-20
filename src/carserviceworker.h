#ifndef CARSERVICEWORKER_H
#define CARSERVICEWORKER_H


#include "qlcdnumber.h"
#include "qobject.h"
class CarServiceWorker : public QObject
{
    Q_OBJECT
public:
    CarServiceWorker(QLCDNumber* time);
    ~CarServiceWorker();
    static bool run;
public slots:
    void process();
signals:
    void finished();
    void error(QString err);
private:
        QLCDNumber* lcd;
    int counter=0;
};

#endif // CARSERVICEWORKER_H
