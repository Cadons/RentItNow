#include "carmodel.h"
#include "../service/carmanagmentservice.h"
CarModel::CarModel(map<string, std::shared_ptr<Car>> data,QObject *parent)
    : QAbstractTableModel{parent}
{
     updateData();
}

int CarModel::rowCount(const QModelIndex &parent) const
{
    return carsData.size();
}

int CarModel::columnCount(const QModelIndex &parent) const
{
    return 8;
}

QVariant CarModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole)
    {

     const Car* obj = carsData.at(keys[index.row()]).get();
        switch (index.column()) {
        case 0:
            return QString(QString::fromStdString(obj->getName()));
            break;
        case 1:
            return QString(QString::fromStdString(obj->getBrand()));
            break;
        case 2:
            return QString(QString::fromStdString(obj->getLicensePlate()));
            break;
        case 3:
            return QString(QString::fromStdString(obj->getTypeName()));
            break;
        case 4:
            return obj->getKmBeforeService();
        case 5:
          return CarManagmentService::getInstance().checkAviability(obj->getLicensePlate())?   QString("Available"):     QString("Not Available");
        case 6:
          return obj->getTotalKm();
        case 7:
          return 0;//obj->getLocation();
        }




    }
    return QVariant();
}

void CarModel::updateData()
{
    carsData=CarManagmentService::getInstance().getCars();
    keys.clear();
    for(const auto& e: carsData){
        keys.push_back(e.first);
    }
}

QVariant CarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal)
    {
        switch (section) {
        case 0: return "Name";
        case 1: return "Brand";
        case 2: return "License Plate";
        case 3: return "Type";
        case 4: return "Km before service";
        case 5: return "Aviability";
        case 6: return "Total Km";
        case 7: return "Location";
        }
    }
    return QVariant();
}

Car *CarModel::getCar(int index)
{
    return carsData.at(keys[index]).get();
}
