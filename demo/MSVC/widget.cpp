#include "widget.h"

#include <QPushButton>

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include "OE/OEasyScreenshot"
#include "qxt/qxtglobalshortcut.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
  openScreenshotButton_(new QPushButton(this)) {

    openScreenshotButton_->setGeometry(0,0,300,300);
    openScreenshotButton_->setObjectName("OpenScreenshotButton");
    openScreenshotButton_->show();
    openScreenshotButton_->setText(QStringLiteral("µ¥»÷ÎÒ\n\n¿ì½Ý¼ü( Shift+A )"));

    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(QKeySequence("Shift+A"), this);
    connect(shortcut, SIGNAL(activated()),
            this, SLOT(onScreenshot()));
    connect(openScreenshotButton_.get(), SIGNAL(clicked()),
            this, SLOT(onScreenshot()));
}


void Widget::onScreenshot()
{
    OEScreenshot::Instance();
}
