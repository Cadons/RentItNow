#ifndef ISINGLEDATAREPOSITORY_H
#define ISINGLEDATAREPOSITORY_H
#include "qjsonobject.h"
#include <memory>
template <typename T>
class ISingleDataRepository
{
public:
    virtual std::unique_ptr<T> load()=0;
    virtual bool save(T* data)=0;
    virtual QJsonObject convertObjectToJson(T* obj)=0;
    virtual std::unique_ptr<T> convertJsonToObject(std::string& obj)=0;
};
#endif // ISINGLEDATAREPOSITORY_H
