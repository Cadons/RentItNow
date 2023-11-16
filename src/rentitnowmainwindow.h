#ifndef RENTITNOWMAINWINDOW_H
#define RENTITNOWMAINWINDOW_H

#include "carmanager.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class RentItNowMainWindow; }
QT_END_NAMESPACE

class RentItNowMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    RentItNowMainWindow(QWidget *parent = nullptr);
    ~RentItNowMainWindow();

private slots:
    void on_actionCar_Managment_triggered();

    void on_actionI_m_Boss_triggered();

    void on_actionI_m_User_triggered();


private:
    Ui::RentItNowMainWindow *ui;
    CarManager* carManager;
    bool isBoss;
};
#endif // RENTITNOWMAINWINDOW_H
