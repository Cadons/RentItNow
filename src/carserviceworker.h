#ifndef CARSERVICEWORKER_H
#define CARSERVICEWORKER_H


#include "qobject.h"
class CarServiceWorker : public QObject
{
    Q_OBJECT
public:
    CarServiceWorker();
    ~CarServiceWorker();
public slots:
    void process();
signals:
    void finished();
    void error(QString err);
};

#endif // CARSERVICEWORKER_H
