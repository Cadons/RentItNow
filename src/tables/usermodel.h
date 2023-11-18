#ifndef USERMODEL_H
#define USERMODEL_H

#include <QAbstractTableModel>
#include "../model/user.h"
class UserModel : public QAbstractTableModel
{
public:
    explicit UserModel(std::map<std::string, std::shared_ptr<User>> data,QObject *parent = nullptr);

private:
    std::map<std::string, std::shared_ptr<User>> users;
    std::vector<std::string> keys;
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    User* getUser(int index);

};

#endif // USERMODEL_H
