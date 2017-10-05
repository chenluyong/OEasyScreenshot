#-------------------------------------------------
#
# Project created by QtCreator 2017-10-05T15:07:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScreenShotLibDemo
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

# lib demo core begin
DESTDIR   = ../../bin/
# 在启动之前先生成ScreenShotLib (before building the demo, build ScreenShot library)
# lib demo core end


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    +=
