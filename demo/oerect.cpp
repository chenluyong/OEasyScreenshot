#include "oerect.h"
#include <QPainter>
#ifndef QT_NO_DEBUG
#include <QDebug>
#endif
#include "oecommonhelper.h"
OERect::OERect(QWidget *parent) : QWidget(parent)
{
    backgroundPixmap_ = new QPixmap(width(),height());
    backgroundPixmap_->fill((QColor(0, 174, 255, 60)));

    setFixedSize(95 * OECommonHelper::getWindowWidthMultiplyingPower(),
                 20 * OECommonHelper::getWindowHeightMultiplyingPower());
    hide();
}


void OERect::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(rect(),*backgroundPixmap_);
    painter.setPen(QPen(QColor(Qt::white)));
    painter.drawText(rect(), Qt::AlignCenter, info_);
}

void OERect::onPostionChange(int x, int y) {
    const int& ry = y - height();
    if (ry < 0) {
        this->raise();
    }
    move(x, ((ry < 0) ? y : ry));
}

void OERect::onSizeChange(int w, int h) {
    info_ = QString("%1 × %2").arg(w).arg(h);
}
