#ifndef CARMODEL_H
#define CARMODEL_H
#include <string>
#include <map>
#include "../model/car.h"
#include <QAbstractTableModel>

class CarModel : public QAbstractTableModel
{
public:
    explicit CarModel(map<string, std::shared_ptr<Car>> data,QObject *parent = nullptr);


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;


private:
    map<string, std::shared_ptr<Car>> carsData;
    vector<string> keys;
    void updateData();

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Car *getCar(int index);
};

#endif // CARMODEL_H
