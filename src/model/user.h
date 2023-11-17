#ifndef USER_H
#define USER_H

#include <string>
#include <QUuid>

class User {
private:
    std::string id;
    std::string name;
    std::string surname;
    std::string address;
    std::string creditCard;
    std::string drivingLicense;

public:
    // Constructors
    User();  // Default constructor
    User(const std::string& name, const std::string& surname, const std::string& address,
         const std::string& creditCard, const std::string& drivingLicense);
    User(const std::string &id, const std::string &name, const std::string &surname, const std::string &address, const std::string &creditCard, const std::string &drivingLicense);

    std::string getName() const;
    void setName(const std::string &newName);
    std::string getSurname() const;
    void setSurname(const std::string &newSurname);
    std::string getAddress() const;
    void setAddress(const std::string &newAddress);
    std::string getCreditCard() const;
    void setCreditCard(const std::string &newCreditCard);
    std::string getDrivingLicense() const;
    void setDrivingLicense(const std::string &newDrivingLicense);
    std::string getId() const;
    std::string toString();
    bool operator ==(const User& other)const;

    void setId(const std::string &newId);
};

#endif // USER_H
