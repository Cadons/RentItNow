#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <QWidget>
#include "carform.h"
#include "qabstractitemmodel.h"
#include "service/ICarManager.h"
namespace Ui {
class CarManager;
}

class CarManager : public QWidget
{
    Q_OBJECT

public:
    explicit CarManager(QWidget *parent = nullptr);
    ~CarManager();
private slots:




    void on_carsTable_clicked(const QModelIndex &index);


    void on_edit_pushButton_clicked();

    void on_CarManagment_currentChanged(int index);

    void on_delete_pushButton_clicked();

private:
    Ui::CarManager *ui;
    ICarManager& carManager;
    std::unique_ptr<CarForm> newForm;
    std::unique_ptr<CarForm> editForm;
    Car* selectedCar;
    void updateTable();


};

#endif // CARMANAGER_H
