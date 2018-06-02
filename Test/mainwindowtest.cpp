#include "mainwindowtest.h"
#include "../.ui/ui_mainwindow.h"
#include <QMenuBar>
#include <QTest>
#include <QSignalSpy>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

namespace
{
    constexpr int TIMEOUT_MS = 3000;
}

template<class T>
T* MainWindowTest::findUnparentedWidget(T *foundWidget)
{
    auto unparentedWidgets(QApplication::topLevelWidgets());
    foreach (auto widget, unparentedWidgets)
    {
        foundWidget = dynamic_cast<T*>(widget);
        if(Q_NULLPTR != foundWidget)
        {
            qDebug(QString("Found widget %1 at %2 (%3)")
                  .arg(foundWidget->objectName())
                  .arg(QString::number(reinterpret_cast<uintptr_t>(foundWidget), 16))
                  .arg(QString::number(reinterpret_cast<uintptr_t>(widget), 16))
                  .toUtf8().constData());
            break;
        }
    }

    return foundWidget;
}

// will be called before each test function is executed.
void MainWindowTest::init()
{
    MainWin.reset(new AdventureMain::MainWindow());
    MainWin->show();

    QTEST_ASSERT(MainWin->isVisible());
}

void MainWindowTest::exitGameWhenExitClickedInMenu()
{
    MainWin->findChild<QAction*>("actionExit")->trigger();
    QTRY_VERIFY_WITH_TIMEOUT(MainWin->isVisible() == false, TIMEOUT_MS);
}

void MainWindowTest::showAboutMessageWhenAboutClicked()
{
    auto actionAbout(MainWin->findChild<QAction*>("actionAbout"));
    QMessageBox* aboutBox(Q_NULLPTR);

    auto earlyTimerMessageBoxBypass = [this, aboutBox] () mutable
    {
        aboutBox = findUnparentedWidget(aboutBox);
        QTEST_ASSERT(Q_NULLPTR != aboutBox);

        QVERIFY(aboutBox->objectName() == "AboutWindow");
        QVERIFY(aboutBox->text() == "Brandon's Adventure\ncopyright Brandon Heins");

        aboutBox->close();
    };

    QTimer::singleShot(0, earlyTimerMessageBoxBypass);
    actionAbout->trigger();

    MainWin->findChild<QAction*>("actionExit")->trigger();
    QTRY_VERIFY_WITH_TIMEOUT(MainWin->isVisible() == false, TIMEOUT_MS);
}

QTEST_MAIN(MainWindowTest)
