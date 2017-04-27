#include "oescreen.h"
#include <QApplication>
#include <QMouseEvent>

#include <QPen>
#include <QPainter>
#include <QMenu>
#include <QDateTime>
#include <QFileDialog>
#include <QClipboard>

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

OEScreen::OEScreen(QPixmap *originPainting, QPoint pos, QWidget *parent)
    : QWidget(parent),isInit_(false), direction_(NONE), originPoint_(pos),
      isPressed_(false), originPainting_(originPainting) {
    menu_ = new QMenu(this);
    menu_->addAction("完成截图", this, SLOT(onSaveScreen()));
    menu_->addAction("保存", this, SLOT(onSaveScreenOther()));
    menu_->addSeparator();
    menu_->addAction("退出截图", this, SLOT(quitScreenshot()));

    // 双击即完成
    connect(this, SIGNAL(doubleClick()),
            this, SLOT(onSaveScreen()));

    // 设置成无边框对话框
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
    this->setMouseTracking(true);
}

OEScreen::DIRECTION OEScreen::getRegion(const QPoint &cursor) {
    if (!isInit_) {
        return NONE;
    }
    OEScreen::DIRECTION ret_dir = NONE;
    QPoint ptopleft = mapToParent(rect().topLeft());
    QPoint prightbottom = mapToParent(rect().bottomRight());

    int x = cursor.x();
    int y = cursor.y();

    if(ptopleft.x() + PADDING_ >= x
    && ptopleft.x() <= x
    && ptopleft.y() + PADDING_ >= y
    && ptopleft.y() <= y) {
        // 左上角
        ret_dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x >= prightbottom.x() - PADDING_
           && x <= prightbottom.x()
           && y >= prightbottom.y() - PADDING_
           && y <= prightbottom.y()) {
        // 右下角
        ret_dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= ptopleft.x() + PADDING_
           && x >= ptopleft.x()
           && y >= prightbottom.y() - PADDING_
           && y <= prightbottom.y()) {
        //左下角
        ret_dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= prightbottom.x()
           && x >= prightbottom.x() - PADDING_
           && y >= ptopleft.y()
           && y <= ptopleft.y() + PADDING_) {
        // 右上角
        ret_dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= ptopleft.x() + PADDING_
           && x >= ptopleft.x()) {
        // 左边
        ret_dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= prightbottom.x()
            && x >= prightbottom.x() - PADDING_) {
        // 右边
        ret_dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= ptopleft.y()
          && y <= ptopleft.y() + PADDING_){
        // 上边
        ret_dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= prightbottom.y()
           && y >= prightbottom.y() - PADDING_) {
        // 下边
        ret_dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        ret_dir = NONE;
        this->setCursor(QCursor(Qt::SizeAllCursor));
    }
    return ret_dir;
}


void OEScreen::contextMenuEvent(QContextMenuEvent *) {
    // 在鼠标位置弹射出菜单栏
    menu_->exec(cursor().pos());
}

void OEScreen::mouseDoubleClickEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        emit doubleClick();
        e->accept();
    }
}

void OEScreen::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        isPressed_ = true;
        if(direction_ != NONE) {
            this->mouseGrabber();
        }
        movePos_ = e->globalPos() - pos();
    }
}

void OEScreen::mouseReleaseEvent(QMouseEvent * e) {
    if (e->button() == Qt::LeftButton) {
        isPressed_ = false;
        if(direction_ != NONE) {
            releaseMouse();
            setCursor(QCursor(Qt::SizeAllCursor));
        }
    }
}
void OEScreen::mouseMoveEvent(QMouseEvent * e) {
    QPoint gloPoint = mapToParent(e->pos());
    QPoint ptopleft = mapToParent(rect().topLeft());
    QPoint pleftbottom = mapToParent(rect().bottomLeft());
    QPoint prightbottom = mapToParent(rect().bottomRight());
    QPoint prighttop = mapToParent(rect().topRight());
    if(!isPressed_) {
        // 检查鼠标鼠标位置
        direction_ = getRegion(gloPoint);

        // 根据方位判断拖拉对应支点
        switch(direction_) {
        case NONE:
        case RIGHT:
        case RIGHTBOTTOM:
            originPoint_ = ptopleft;
            break;
        case RIGHTTOP:
            originPoint_ = pleftbottom;
            break;
        case LEFT:
        case LEFTBOTTOM:
            originPoint_ = prighttop;
            break;
        case LEFTTOP:
        case UP:
            originPoint_ = prightbottom;
            break;
        case DOWN:
            originPoint_ = ptopleft;
            break;
        }
    }
    else {
        if(direction_ != NONE) {
            const int& global_x = gloPoint.x();
            // 鼠标进行拖拉拽
            switch(direction_) {
            case LEFT:
                return onMouseChange(global_x, pleftbottom.y() + 1);
            case RIGHT:
                return onMouseChange(global_x, prightbottom.y() + 1);
            case UP:
                return onMouseChange(global_x, gloPoint.y());
            case DOWN:
                return onMouseChange(prightbottom.x() + 1, gloPoint.y());
            case LEFTTOP:
            case RIGHTTOP:
            case LEFTBOTTOM:
            case RIGHTBOTTOM:
                return onMouseChange(global_x, gloPoint.y());
            default:
                break;
            }
        }
        else {
            // 窗口的移动
            move(e->globalPos() - movePos_);
            movePos_ = e->globalPos() - pos();
            emit postionChange(pos().x(),pos().y());
            e->accept();
        }
    }
    currentRect_ = geometry();
}

void OEScreen::enterEvent(QEvent *e) {
    setCursor(Qt::SizeAllCursor);
    QWidget::enterEvent(e);
}

void OEScreen::leaveEvent(QEvent *e) {
    setCursor(Qt::ArrowCursor);
    QWidget::leaveEvent(e);
}

void OEScreen::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    // 绘制截屏编辑窗口
    painter.drawPixmap(QPoint(0,0),
       *originPainting_, currentRect_);

    // 绘制边框线
    QPen pen(QColor(0,174,255),2);
    painter.setPen(pen);
    painter.drawRect(rect());

    // 绘制点
    pen.setWidth(4); //改变点的宽度
    pen.setColor(Qt::red);
    painter.setPen(pen);
    QPolygon temp_anchors;
    // 角点
    temp_anchors.push_back(QPoint(0, 0));
    temp_anchors.push_back(QPoint(width(), 0));
    temp_anchors.push_back(QPoint(0, height()));
    temp_anchors.push_back(QPoint(width(), height()));

    // 中点
    temp_anchors.push_back(QPoint((width() >> 1), 0));
    temp_anchors.push_back(QPoint((width() >> 1), height()));
    temp_anchors.push_back(QPoint(0, (height() >> 1)));
    temp_anchors.push_back(QPoint(width(), (height() >> 1)));
    painter.drawPoints(temp_anchors);
}

const QString OEScreen::getFileName(void) {
    QString file_name = QDateTime::currentDateTime().toString("CSDN博客_瓯裔_yyyy-MM-dd-HH-mm-ss");
    return file_name;
}


void OEScreen::onSaveScreenOther(void) {

    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", getFileName(), "JPEG Files (*.jpg)");
    if (fileName.length() > 0) {
        originPainting_->copy(currentRect_).save(fileName, "jpg");
        quitScreenshot();
    }
}

void OEScreen::onSaveScreen(void) {
    // 把图片放入剪切板
    QClipboard *board = QApplication::clipboard();
    board->setPixmap(originPainting_->copy(currentRect_));
    quitScreenshot();
}


void OEScreen::quitScreenshot(void) {
    close();
    parentWidget()->close();
}

void OEScreen::onMouseChange(int w, int h) {
    show();
    if (w < 0 || h < 0) {
        return;
    }
    const int& rx = (w >= originPoint_.x()) ? originPoint_.x() : w;
    const int& ry = (h >= originPoint_.y()) ? originPoint_.y() : h;
    const int& rw = abs(w - originPoint_.x());
    const int& rh = abs(h - originPoint_.y());

    // 改变大小
    currentRect_ = QRect(rx, ry, rw, rh);
    emit sizeChange(rw, rh);

    this->setGeometry(currentRect_);
    emit postionChange(currentRect_.x(),currentRect_.y());
    // 改变大小后更新父窗口，防止父窗口未及时刷新而导致的问题
    parentWidget()->update();
}
