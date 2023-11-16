#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <QWidget>
#include "qabstractitemmodel.h"
#include "service/ICarManager.h"
#include "tables/carmodel.h"
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

    void on_addCar_pushButton_clicked();

    void on_reset_pushButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_carsTable_clicked(const QModelIndex &index);


    void on_edit_pushButton_clicked();

private:
    Ui::CarManager *ui;
    ICarManager& carManager;
    void cleanForm();
    Car* selectedCar;


};

#endif // CARMANAGER_H
