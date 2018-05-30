include(Common.pri)
TEMPLATE = subdirs
SUBDIRS = App Main Test
LANGUAGE = C++11
CONFIG += ordered

Main.depends = App
Test.depends = App

