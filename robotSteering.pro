#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T11:01:55
#
#-------------------------------------------------

QT       += core gui sensors bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robotSteering
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

