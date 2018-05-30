#pragma once

#include <QMainWindow>
#include <QObject>
#include <QScopedPointer>

namespace Ui
{
    class MainWindow;
}

namespace AdventureMain
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = Q_NULLPTR);
        ~MainWindow();

    private:
        void about();
        void exit();

        QScopedPointer<Ui::MainWindow> Map;
    };
}
