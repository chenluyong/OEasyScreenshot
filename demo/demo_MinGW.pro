#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T10:52:23
#
#-------------------------------------------------

QT       += core gui
CONFIG   += C++11
DESTDIR   = ../bin
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app
INCLUDEPATH += "../src/"
include(MinGW/qxt/qxt.pri)

SOURCES += MinGW/main.cpp\
        MinGW/widget.cpp \
    ../src/OE/oescreenshot/oeamplifier.cpp \
    ../src/OE/oescreenshot/oecommonhelper.cpp \
    ../src/OE/oescreenshot/oemodelview.cpp \
    ../src/OE/oescreenshot/oescreenshot.cpp

HEADERS  += MinGW/widget.h \
    ../src/OE/oescreenshot/oeamplifier.h \
    ../src/OE/oescreenshot/oecommonhelper.h \
    ../src/OE/oescreenshot/oemodelview.h \
    ../src/OE/oescreenshot/oescreenshot.h

