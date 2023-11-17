#ifndef USERMANAGEMENTSERVICE_H
#define USERMANAGEMENTSERVICE_H

#include "IUserManager.h"

class UserManagementService : public IUserManager
{
private:
    UserManagementService();
    std::map<std::string, std::shared_ptr<User> > myUsers;

    // ICrud interface
public:
    bool add(User* newObject) override;
    bool update(std::string key, User* updatedObject) override;
    bool remove(User* objectToDelete) override;
    bool remove(std::string key) override;

    // IUserManager interface
public:
    std::map<std::string, std::shared_ptr<User> > getUsers() override;
    User *getUser(std::string id) override;
    bool validateDrivingLicense(std::string dl, std::string  id) override;
    int usersCount() override;
    void clearAll();
    static UserManagementService& getInstance();


};

#endif // USERMANAGEMENTSERVICE_H
