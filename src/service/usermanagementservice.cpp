#include "usermanagementservice.h"
#include "../repository/usersrepository.h"
UserManagementService::UserManagementService()
{
    this->myUsers=UsersRepository::getInstance().load();
}

UserManagementService::~UserManagementService()
{
    UsersRepository::getInstance().save(myUsers);
}

bool UserManagementService::add(User *newObject)
{
    if(newObject!=nullptr)
    {
        if(!this->myUsers.empty())
            if (!validateDrivingLicense(newObject->getDrivingLicense()))
                return false;
        this->myUsers[newObject->getDrivingLicense()] = std::make_shared<User>(*newObject);

        return UsersRepository::getInstance().save(myUsers);
    }else{
        return false;
    }
}

bool UserManagementService::update(std::string key, User *updatedObject)
{
    //search the object by licencse plate
    if(updatedObject==nullptr)
        return false;
    if(key!="")
    {
        if(updatedObject->getDrivingLicense().empty())
            return false;
        if(key!=updatedObject->getDrivingLicense())
        {
            if(validateDrivingLicense(updatedObject->getDrivingLicense()))
            {
                if(remove(key))//Delete old element
                    return add(updatedObject);
                return false;
            }
            else
                return false;

        }
        if(myUsers.count(key)>0){
            if(updatedObject->getName()!="")
                myUsers[key].get()->setName(updatedObject->getName());
            if(updatedObject->getSurname()!="")
                myUsers[key].get()->setSurname(updatedObject->getSurname());
            if(updatedObject->getAddress()!="")
                myUsers[key].get()->setAddress(updatedObject->getAddress());
            if(updatedObject->getCreditCard()!="")
                myUsers[key].get()->setCreditCard(updatedObject->getCreditCard());

        }

        return UsersRepository::getInstance().save(myUsers);


    }else{
        return false;
    }
}

bool UserManagementService::remove(User *objectToDelete)
{
    if(objectToDelete!=nullptr&&myUsers.size()>0){
        myUsers.erase(objectToDelete->getDrivingLicense());
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

bool UserManagementService::validateDrivingLicense(std::string dl)
{
    for (const auto& it : myUsers) {

        if(it.second->getDrivingLicense()==dl)
            return false;


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
