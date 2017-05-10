#include "widget.h"
#include "ui_widget.h"

#include <QPushButton>

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include "oescreenshot/oescreenshot.h"
#include "qxt/qxtglobalshortcut.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
  openScreenshotButton_(new QPushButton(this)) {

    ui->setupUi(this);
    openScreenshotButton_->setGeometry(0,0,300,300);
    openScreenshotButton_->setObjectName("OpenScreenshotButton");
    openScreenshotButton_->show();
    openScreenshotButton_->setText("单击我\n\n快捷键( Shift+A )");

    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(QKeySequence("Shift+A"), this);
    connect(shortcut, SIGNAL(activated()),
            this, SLOT(onScreenshot()));
    connect(openScreenshotButton_.get(), SIGNAL(clicked()),
            this, SLOT(onScreenshot()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onScreenshot()
{
    OEScreenshot::Instance();
}
