#-------------------------------------------------
#
# Project created by QtCreator 2016-02-11T18:09:59
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multimeterGUI
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    serialport.cpp \
    rs22812.cpp \
    lcd.cpp

HEADERS  += mainwindow.h \
    serialport.h \
    rs22812.h \
    lcd.h

FORMS    += mainwindow.ui
