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
            if (validateDrivingLicense(newObject->getDrivingLicense()))
                return false;
        this->myUsers[newObject->getId()] = std::make_shared<User>(*newObject);

        return UsersRepository::getInstance().save(myUsers);
    }else{
        return false;
    }
}

bool UserManagementService::update(std::string key, User *updatedObject)
{

}

bool UserManagementService::remove(User *objectToDelete)
{

}

bool UserManagementService::remove(std::string key)
{

}

std::map<std::string, std::shared_ptr<User> > UserManagementService::getUsers()
{

}

User *UserManagementService::getUser(std::string id)
{

}

bool UserManagementService::validateDrivingLicense(std::string dl)
{
    for (const auto& it : myUsers) {
        if(it.second->getDrivingLicense()==dl)
            return false;
    }
    return true;
}

UserManagementService &UserManagementService::getInstance()
{
    static UserManagementService instance;
    return instance;
}
