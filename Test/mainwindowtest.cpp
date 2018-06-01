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
bool MainWindowTest::findUnparentedWidget(T *foundWidget)
{
    auto unparentedWidgets(QApplication::topLevelWidgets());
    foreach (auto widget, unparentedWidgets)
    {
        foundWidget = dynamic_cast<T*>(widget);
        if(Q_NULLPTR != foundWidget)
        {
            qInfo(QString("Found widget %1 at %2 (%3)")
                  .arg(foundWidget->objectName())
                  .arg(QString::number(reinterpret_cast<uintptr_t>(foundWidget), 16))
                  .arg(QString::number(reinterpret_cast<uintptr_t>(widget), 16))
                  .toUtf8().constData());
            break;
        }
    }

    return (Q_NULLPTR != foundWidget);
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
    qInfo(QString("aboutBox ptrAddress=%1 objAddress=%2")
          .arg(QString::number(reinterpret_cast<uintptr_t>(&aboutBox), 16))
          .arg(QString::number(reinterpret_cast<uintptr_t>(aboutBox), 16))
          .toUtf8().constData());

    auto earlyTimerMessageBoxBypass = [this, aboutBox] ()
    {
        QVERIFY(findUnparentedWidget(aboutBox));

        qInfo(QString("aboutBox ptrAddress=%1 objAddress=%2")
              .arg(QString::number(reinterpret_cast<uintptr_t>(&aboutBox), 16))
              .arg(QString::number(reinterpret_cast<uintptr_t>(aboutBox), 16))
              .toUtf8().constData());

        QVERIFY(Q_NULLPTR != aboutBox);
    };

    QTimer::singleShot(200, earlyTimerMessageBoxBypass);
    actionAbout->trigger();

    QTEST_ASSERT(Q_NULLPTR != aboutBox);
    if(!QTest::currentTestFailed())
    {
        QVERIFY(aboutBox->objectName() == "AboutWindow");
        QVERIFY(aboutBox->hasFocus());
        QVERIFY(aboutBox->text() == "Brandon's Adventure\ncopyright Brandon Heins");

        aboutBox->close();
    }
    qInfo(QString("AboutBox=%1").arg(reinterpret_cast<uintptr_t>(aboutBox)).toUtf8().constData());

    QTRY_VERIFY_WITH_TIMEOUT(MainWin->hasFocus(), TIMEOUT_MS);
    MainWin->findChild<QAction*>("actionExit")->trigger();
    QTRY_VERIFY_WITH_TIMEOUT(MainWin->isVisible() == false, TIMEOUT_MS);
}

QTEST_MAIN(MainWindowTest)
