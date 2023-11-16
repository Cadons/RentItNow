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
    CarForm* newForm;
    CarForm* editForm;
    Car* selectedCar;


};

#endif // CARMANAGER_H
