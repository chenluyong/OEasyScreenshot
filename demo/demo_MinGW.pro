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
    ../src/oescreenshot/oeamplifier.cpp \
    ../src/oescreenshot/oecommonhelper.cpp \
    ../src/oescreenshot/oemodelview.cpp \
    ../src/oescreenshot/oescreenshot.cpp

HEADERS  += MinGW/widget.h \
    ../src/oescreenshot/oeamplifier.h \
    ../src/oescreenshot/oecommonhelper.h \
    ../src/oescreenshot/oemodelview.h \
    ../src/oescreenshot/oescreenshot.h

FORMS    += MinGW/widget.ui
