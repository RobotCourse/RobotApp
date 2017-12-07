#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T12:12:27
#
#-------------------------------------------------

QT       += core gui
CONFIG +=c++11 c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobotApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

PROJNAME = RobotApp
INSTTYPE = APP
include(RobotSDK_Main.pri)

LIBS += -L/home/mini/OpenNI-Linux-x64-2.3/Redist -lOpenNI2
