#include "usermanagementservice.h"
#include "../repository/usersrepository.h"
UserManagementService::UserManagementService()
{

}

bool UserManagementService::add(User *newObject)
{
    if(newObject!=nullptr)
    {
        if(!this->myUsers.empty())
            if (!validateDrivingLicense(newObject->getDrivingLicense(), newObject->getId())||myUsers.count(newObject->getId())>0)
                return false;
        this->myUsers[newObject->getId()] = std::make_shared<User>(*newObject);

        return UsersRepository::getInstance().save(myUsers);
    }else{
        return false;
    }
}

bool UserManagementService::update(std::string key, User *updatedObject)
{
    //search the object by licencse plate
    if(key!=""&&updatedObject!=nullptr&&myUsers[key]!=nullptr&&key==updatedObject->getId()&&myUsers.count(key)>0)
    {
        if(updatedObject->getDrivingLicense()!=""&&validateDrivingLicense(updatedObject->getDrivingLicense(), updatedObject->getId()))
            myUsers[key].get()->setDrivingLicense(updatedObject->getDrivingLicense());
        else
            return false;

        if(updatedObject->getName()!="")
            myUsers[key].get()->setName(updatedObject->getName());
        if(updatedObject->getSurname()!="")
            myUsers[key].get()->setSurname(updatedObject->getSurname());
        if(updatedObject->getAddress()!="")
            myUsers[key].get()->setAddress(updatedObject->getAddress());
        if(updatedObject->getCreditCard()!="")
            myUsers[key].get()->setCreditCard(updatedObject->getCreditCard());

        return UsersRepository::getInstance().save(myUsers);


    }else{
        return false;
    }
}

bool UserManagementService::remove(User *objectToDelete)
{
    if(objectToDelete!=nullptr&&myUsers.size()>0){
        myUsers.erase(objectToDelete->getId());
        return UsersRepository::getInstance().save(myUsers);
    }
    return false;
}

bool UserManagementService::remove(std::string key)
{
    if(myUsers.count(key)>0)
        return this->remove(myUsers[key].get());
    return false;
}

std::map<std::string, std::shared_ptr<User> > UserManagementService::getUsers()
{
    return myUsers;
}

User *UserManagementService::getUser(std::string id)
{
    if(id.empty())
        return nullptr;
    else
        return this->myUsers[id].get();
}

bool UserManagementService::validateDrivingLicense(std::string dl, std::string id)
{
    for (const auto& it : myUsers) {
        if(it.second->getId()!=id)
        {
            if(it.second->getDrivingLicense()==dl)
                return false;
        }

    }
    return true;
}



int UserManagementService::usersCount()
{
    return myUsers.size();
}

void UserManagementService::clearAll()
{
    myUsers.clear();
}

UserManagementService &UserManagementService::getInstance()
{
    static UserManagementService instance;
    return instance;
}
