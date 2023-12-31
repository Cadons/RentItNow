#include "user.h"

std::string User::getName() const
{
    return name;
}

void User::setName(const std::string &newName)
{
    name = newName;
}

std::string User::getSurname() const
{
    return surname;
}

void User::setSurname(const std::string &newSurname)
{
    surname = newSurname;
}

std::string User::getAddress() const
{
    return address;
}

void User::setAddress(const std::string &newAddress)
{
    address = newAddress;
}

std::string User::getCreditCard() const
{
    return creditCard;
}

void User::setCreditCard(const std::string &newCreditCard)
{
    creditCard = newCreditCard;
}

std::string User::getDrivingLicense() const
{
    return drivingLicense;
}

void User::setDrivingLicense(const std::string &newDrivingLicense)
{
    drivingLicense = newDrivingLicense;
}


std::string User::toString()
{
    std::string result = "User {";
    result += "name: " + name + ", ";
    result += "surname: " + surname + ", ";
    result += "address: " + address + ", ";
    result += "creditCard: " + creditCard + ", ";
    result += "drivingLicense: " + drivingLicense + "}";
    return result;
}

bool User::operator ==(const User &other) const
{
    return
           name == other.name &&
           surname == other.surname &&
           address == other.address &&
           creditCard == other.creditCard &&
           drivingLicense == other.drivingLicense;
}




User::User()
{

}

User::User(const std::string& name, const std::string& surname, const std::string& address,
           const std::string& creditCard, const std::string& drivingLicense)
    : name(name), surname(surname), address(address), creditCard(creditCard), drivingLicense(drivingLicense) {

}

User::User(User &user): name(user.name), surname(user.surname), address(user.address), creditCard(user.creditCard), drivingLicense(user.drivingLicense)
{

}

