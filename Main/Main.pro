include(../Common.pri)
QT += gui core widgets

CONFIG += c++11 console
CONFIG -= app_bundle

DEPENDPATH += . $$DESTDIR/../lib
INCLUDEPATH += ../App ../Public  ../.ui/

OBJECTS_DIR = $$DESTDIR/.obj
#MOC_DIR = $$DESTDIR/.moc
#RCC_DIR = $$DESTDIR/.qrc
#UI_DIR = $$DESTDIR/.ui

SOURCES = main.cpp
LIBS += -L$$DESTDIR/../lib -lApp
DESTDIR = $$DESTDIR/../
TARGET = brandonsadventure
