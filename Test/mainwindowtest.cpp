#include "mainwindowtest.h"
#include "../.ui/ui_mainwindow.h"
#include <QMenuBar>
#include <QTest>
#include <QSignalSpy>
#include <QDebug>
#include <QTimer>

namespace
{
    constexpr int TIMEOUT_MS = 3000;
}

template<class T>
bool MainWindowTest::findUnparentedWidget(T *foundWidget)
{
    const QWidgetList unparentedWidgets(QApplication::topLevelWidgets());
    foreach (const QWidget* widget, unparentedWidgets)
    {
        foundWidget = const_cast<T*>(dynamic_cast<const T*>(widget));
        if(foundWidget)
        {
            qInfo(QString("Found widget %1").arg(foundWidget->objectName()).toLatin1().constData());
            break;
        }
    }
    return (foundWidget != NULL);
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
    QAction* actionAbout(MainWin->findChild<QAction*>("actionAbout"));
    QMessageBox* aboutBox(Q_NULLPTR);

    auto func = [&, aboutBox] () mutable
    {
        QTRY_VERIFY_WITH_TIMEOUT(findUnparentedWidget(aboutBox), TIMEOUT_MS);
        QTEST_ASSERT(Q_NULLPTR != aboutBox);

        if(!QTest::currentTestFailed())
        {
            QVERIFY(aboutBox->objectName() == "AboutWindow");
            QVERIFY(aboutBox->hasFocus());
            QVERIFY(aboutBox->text() == "Brandon's Adventure\ncopyright Brandon Heins");

            aboutBox->close();
        }
    };
    QTimer::singleShot(0, func);

    actionAbout->trigger();

    QTRY_VERIFY_WITH_TIMEOUT(MainWin->hasFocus(), TIMEOUT_MS);
    MainWin->findChild<QAction*>("actionExit")->trigger();
    QTRY_VERIFY_WITH_TIMEOUT(MainWin->isVisible() == false, TIMEOUT_MS);
}

QTEST_MAIN(MainWindowTest)
