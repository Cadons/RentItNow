#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include <memory>
#include <map>
#include <QJsonObject>
template <typename S, typename T>
class IRepository
{
public:
    virtual std::map<S, std::shared_ptr<T>> load()=0;
    virtual bool save(std::map<S, std::shared_ptr<T>> data)=0;
    virtual QJsonObject convertObjectToJson(T obj)=0;
    virtual std::shared_ptr<T> convertJsonToObject(std::string& obj)=0;
};
#endif // IREPOSITORY_H
