#include "rentitnowmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RentItNowMainWindow w;
    w.show();
    return a.exec();
}
