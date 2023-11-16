#ifndef CARFORM_H
#define CARFORM_H

#include "qtabwidget.h"
#include "service/ICarManager.h"
#include <QWidget>

namespace Ui {
class CarForm;
}

class CarForm : public QWidget
{
    Q_OBJECT

public:
    explicit CarForm(Car* car,QTabWidget* tabMenu,QWidget *parent = nullptr);
    explicit CarForm(QWidget *parent = nullptr);

    ~CarForm();

private slots:
    void on_addCar_pushButton_clicked();

    void on_reset_pushButton_clicked();

private:
    Ui::CarForm *ui;
    void cleanForm();
    bool editMode=false;
    QTabWidget* tabMenu;
    Car* carToEdit;
    ICarManager& carManager;
    void back();
};

#endif // CARFORM_H
