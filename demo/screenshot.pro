#��Ȩ���� [2017] [����]

#   ���� Apache ����֤ 2.0 �棨���¼��ơ�����֤������Ȩ��
#   �������ر����ɣ�����������ʹ�������ļ���
#   �����Ի��ø����ɵĸ�����

#        http://www.apache.org/licenses/LICENSE-2.0


#   �������÷�����Ҫ��������ͬ�⣬�������ɷַ�������
#   Ҫ����ԭ�����ַ���û���κ���ʽ�ģ���ȷ�������ĵ������
#   �μ����ձ����ɿ�������Ȩ�޼����Ƶ��ض����Ե�����֤��

#   �����Ի��øô��������°汾��

#        https://git.oschina.net/Mr_ChenLuYong/screenshot

#   ��Դ�����������˶��ڴ������Ĺ�ͬά����


#   ����������Щ���뻹�в������ĵط�����ͨ�����µ����½���ѧϰ��

#        ���͵�ַ��http://blog.csdn.net/csnd_ayo

#        ���µ�ַ��http://blog.csdn.net/csnd_ayo/article/details/70197915

#	�ڴ����ύBug����ӭIssues��



#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T22:20:59
#
#-------------------------------------------------

QT       += core gui
CONFIG += C++11

include(qxt/qxt.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = screenshot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    oescreenshot.cpp \
    oeamplifier.cpp \
    oescreen.cpp \
    oerect.cpp \
    oecommonhelper.cpp \
    oescreenshotwidget.cpp

HEADERS  += oescreenshot.h \
    oeamplifier.h \
    oescreen.h \
    oerect.h \
    oecommonhelper.h \
    oescreenshotwidget.h

DISTFILES +=
