#ifndef RENTITNOWMAINWINDOW_H
#define RENTITNOWMAINWINDOW_H

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

private:
    Ui::RentItNowMainWindow *ui;
};
#endif // RENTITNOWMAINWINDOW_H
