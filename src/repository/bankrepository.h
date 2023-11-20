#ifndef BANKREPOSITORY_H
#define BANKREPOSITORY_H

#include "../model/bank.h"
#include "ISingleDataRepository.h"
#include "qjsonobject.h"
class BankRepository : public ISingleDataRepository<Bank>
{
private:
    BankRepository();

    std::string path="./bank.json";
    // IRepository interface
public:
    std::unique_ptr<Bank> load() override;
    bool save( Bank* data) override;
    QJsonObject convertObjectToJson(Bank*obj) override;
    std::unique_ptr<Bank> convertJsonToObject(std::string &obj) override;
    static BankRepository& getInstance();
};

#endif // BANKREPOSITORY_H
