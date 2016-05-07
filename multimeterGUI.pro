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
    lcd.cpp \
    plotgraph.cpp \
    build-multimeterGUI-Desktop-Debug/moc_datars22812.cpp \
    build-multimeterGUI-Desktop-Debug/moc_foo.cpp \
    build-multimeterGUI-Desktop-Debug/moc_lcd.cpp \
    build-multimeterGUI-Desktop-Debug/moc_lcdscreen.cpp \
    build-multimeterGUI-Desktop-Debug/moc_mainwindow.cpp \
    build-multimeterGUI-Desktop-Debug/moc_plotgraph.cpp \
    build-multimeterGUI-Desktop-Debug/moc_rs22812.cpp \
    build-multimeterGUI-Desktop-Debug/moc_serialport.cpp

HEADERS  += mainwindow.h \
    serialport.h \
    rs22812.h \
    lcd.h \
    plotgraph.h \
    build-multimeterGUI-Desktop-Debug/ui_mainwindow.h

FORMS    += mainwindow.ui

DISTFILES += \
    Doxyfile
