#include "oescreenshotwidget.h"

#include <QPushButton>

#include "oescreenshot.h"
#include "qxt/qxtglobalshortcut.h"

OEScreenshotWidget::OEScreenshotWidget(QWidget *parent) : QWidget(parent),
    openScreenshotButton_(new QPushButton(this))
{
    openScreenshotButton_->show();
    openScreenshotButton_->setGeometry(0,0,300,300);
    openScreenshotButton_->setObjectName("OpenScreenshotButton");
    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(QKeySequence("Shift+A"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(onScreenshot()));

    this->hide();
    openScreenshotButton_->hide();
}

void OEScreenshotWidget::onScreenshot()
{
    OEScreenshot::Instance();
}
