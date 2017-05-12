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
include(MSVC/qxt/qxt.pri)

SOURCES += MSVC/main.cpp\
        MSVC/widget.cpp \
    ../src/oescreenshot_msvc/oeamplifier.cpp \
    ../src/oescreenshot_msvc/oecommonhelper.cpp \
    ../src/oescreenshot_msvc/oemodelview.cpp \
    ../src/oescreenshot_msvc/oescreenshot.cpp

HEADERS  += MSVC/widget.h \
    ../src/oescreenshot_msvc/oeamplifier.h \
    ../src/oescreenshot_msvc/oecommonhelper.h \
    ../src/oescreenshot_msvc/oemodelview.h \
    ../src/oescreenshot_msvc/oescreenshot.h

FORMS    += MSVC/widget.ui
