
QT       += core gui
CONFIG   += C++11
DESTDIR   = ../bin
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET  = OEScreenshot

TEMPLATE = lib

SOURCES += OE/oescreenshot/oeamplifier.cpp \
    OE/oescreenshot/oecommonhelper.cpp \
    OE/oescreenshot/oemodelview.cpp \
    OE/oescreenshot/oescreenshot.cpp

HEADERS  += OE/oescreenshot/oeamplifier.h \
    OE/oescreenshot/oecommonhelper.h \
    OE/oescreenshot/oemodelview.h \
    OE/oescreenshot/oescreenshot.h


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
