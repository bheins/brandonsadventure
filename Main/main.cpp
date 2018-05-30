#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("Brandon's Adventure");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    AdventureMain::MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
