#ifndef IUSERMANAGER_H
#define IUSERMANAGER_H
#include <map>
#include <memory>
#include "../model/user.h"
#include "ICrud.h"
class IUserManager:public ICrud<std::string,User*>
{
public:

    virtual std::map<std::string,std::shared_ptr<User>> getUsers()=0;
    virtual User* getUser(std::string id)=0;
    virtual bool validateDrivingLicense(std::string dl)=0;//dl is unique
    virtual int usersCount()=0;

};
#endif // IUSERMANAGER_H
