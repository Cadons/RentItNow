#include "usermodel.h"

UserModel::UserModel(std::map<std::string, std::shared_ptr<User>> data,QObject *parent)
    : QAbstractTableModel{parent}
{
    this->users=data;
    keys.clear();
    for(const auto& e: users){
        keys.push_back(e.first);
    }
}


int UserModel::rowCount(const QModelIndex &parent) const
{
    return users.size();
}

int UserModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant UserModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole)
    {

        const User* obj = users.at(keys[index.row()]).get();
        switch (index.column()) {
        case 0:
            return QString(QString::fromStdString(obj->getName()));
            break;
        case 1:
            return QString(QString::fromStdString(obj->getSurname()));
            break;
        case 2:
            return QString(QString::fromStdString(obj->getAddress()));
            break;
        case 3:
            return QString(QString::fromStdString(obj->getCreditCard()));
            break;
        case 4:
            return QString(QString::fromStdString(obj->getDrivingLicense()));
        }
    }
    return QVariant();
}

QVariant UserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal)
    {
        switch (section) {
        case 0: return "Name";
        case 1: return "Surname";
        case 2: return "Address";
        case 3: return "Credit Card";
        case 4: return "Driving License";

        }
    }
    return QVariant();
}

User *UserModel::getUser(int index)
{
 return users.at(keys[index]).get();
}
