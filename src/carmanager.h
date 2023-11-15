#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <QWidget>

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
    void on_pushButton_2_clicked();

    void on_resetCar_pushButton_clicked();

    void on_addCar_pushButton_clicked();

    void on_reset_pushButton_clicked();

private:
    Ui::CarManager *ui;
};

#endif // CARMANAGER_H
