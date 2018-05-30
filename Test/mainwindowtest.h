#pragma once

#include "mainwindow.h"
#include <QMessageBox>
#include <QObject>
#include <QScopedPointer>

class MainWindowTest: public QObject
{
    Q_OBJECT

private slots:
    //FRAMEWORK
    void init();// will be called before each test function is executed.

    //TESTS
    void exitGameWhenExitClickedInMenu();
    void showAboutMessageWhenAboutClicked();

private:
    template<class T>
    bool findUnparentedWidget(T *widget);
    QScopedPointer<AdventureMain::MainWindow> MainWin;
};
