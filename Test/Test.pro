QT += core gui widgets testlib
CONFIG += testcase
include(../Common.pri)
DEPENDPATH += . $$DESTDIR/../lib
INCLUDEPATH = $$DESTDIR/../lib ../Public/ ../.ui
TARGET = brandonsadventuretest

SOURCES = mainwindowtest.cpp #main.cpp
HEADERS = mainwindowtest.h

OBJECTS_DIR = $$DESTDIR/../.obj

message(Test.pro looking in=$$DESTDIR/../lib)
LIBS += -L$$DESTDIR/../lib -lApp
DESTDIR = ./
