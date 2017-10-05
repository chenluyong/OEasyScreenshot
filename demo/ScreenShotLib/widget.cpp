#include "widget.h"
#include <QLibrary>
#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    // dll显式加载，只需要dll文件即可，不需要.h和.lib文件
    // 需要将dll放到可执行目录中
    typedef void(*ScreenShortFunc)(void);

    QLibrary lib("OEScreenshot.dll");
    if (lib.load()) {
#ifndef QT_NO_DEBUG
        qDebug() << "load ok!";
#endif

       ScreenShortFunc f = (ScreenShortFunc)lib.resolve("OEScreenshot");
       if (f) {
#ifndef QT_NO_DEBUG
           qDebug() << "load ScreenShortFunc ok!";
#endif
           f();
       }
    } else {
#ifndef QT_NO_DEBUG
        qDebug() << "load error!";
#endif
    }
}

Widget::~Widget()
{
}
