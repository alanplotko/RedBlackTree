#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T15:36:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinalProjectGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rbt.cpp \
    nodegraphic.cpp

HEADERS  += mainwindow.h \
    node.h \
    rbt.h \
    nodegraphic.h

CONFIG += c++11

FORMS    += mainwindow.ui
