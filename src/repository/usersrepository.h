#ifndef USERSREPOSITORY_H
#define USERSREPOSITORY_H

#include "IRepository.h"
#include "../model/user.h"
class UsersRepository : public IRepository<std::string, User>
{
private:
    UsersRepository();
    const std::string path="./usersdb.json";

    // IRepository interface
public:
    std::map<std::string, std::shared_ptr<User>> load() override;
    bool save(std::map<std::string, std::shared_ptr<User> > data) override;
    QJsonObject convertObjectToJson(User obj) override;
    std::shared_ptr<User> convertJsonToObject(std::string &obj) override;
    static UsersRepository& getInstance();

};

#endif // USERSREPOSITORY_H
