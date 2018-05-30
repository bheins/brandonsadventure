include(../Common.pri)
DESTDIR = $$DESTDIR/../lib
QT += gui core widgets
TEMPLATE = lib

INCLUDEPATH += ../Public

SOURCES = mainwindow.cpp
HEADERS = ../Public/mainwindow.h
FORMS = mainwindow.ui

OBJECTS_DIR = $$DESTDIR/../.obj
MOC_DIR = $$DESTDIR/../.moc
RCC_DIR = $$DESTDIR/../.qrc
UI_DIR = $$DESTDIR/../.ui

