#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Set organization and application names to enable saving settings
    a.setOrganizationName(QString("Oscinine Technologies"));
    a.setApplicationName(QString("Fancy Clock"));

    //Make mainWindow a child of QWidget to hide it from taskbar
    QWidget wid;

    MainWindow w(&wid);
    w.show();

    return a.exec();
}
