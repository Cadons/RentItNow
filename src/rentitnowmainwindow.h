#ifndef RENTITNOWMAINWINDOW_H
#define RENTITNOWMAINWINDOW_H

#include "carmanager.h"
#include "usermanager.h"
#include "userrentform.h"
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
    void updateBankValue(float v);
private slots:
    void on_actionCar_Managment_triggered();

    void on_actionI_m_Boss_triggered();

    void on_actionI_m_User_triggered();


    void on_actionUserManagment_triggered();


private:
    Ui::RentItNowMainWindow *ui;
    std::unique_ptr<CarManager> carManager=nullptr;
    std::unique_ptr<UserManager> userManager=nullptr;
    std::unique_ptr<UserRentForm> rentForm=nullptr;
    QThread* tick;

    bool isBoss;
};
#endif // RENTITNOWMAINWINDOW_H
