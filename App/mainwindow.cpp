#include "..\Public\mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QDebug>
using namespace AdventureMain;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent, Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
    , Map(new Ui::MainWindow())
{
    Map->setupUi(this);
    Map->graphicsView->setScene(new QGraphicsScene(this));
    Q_ASSERT(connect(Map->actionExit, &QAction::triggered, this, &MainWindow::exit));
    Q_ASSERT(connect(Map->actionAbout, &QAction::triggered, this, &MainWindow::about));
}

MainWindow::~MainWindow()/* = default;*/
{
    qInfo(__FUNCTION__);
}

void MainWindow::about()
{
    QMessageBox message;
    message.setObjectName("AboutWindow");
    message.setText(QStringLiteral("Brandon's Adventure\ncopyright Brandon Heins"));
    message.show();
    message.exec();
}

void MainWindow::exit()
{
    close();
}
