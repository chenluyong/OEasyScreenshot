/**
 * @author : 陈鲁勇
 * @date   : 2017年04月
 * @version: 1.0
 * @note   : 根据 Apache 许可证 2.0 版（以下简称“许可证”）授权;
 *           除非遵守本许可，否则您不能使用这个文件。
 * @remarks: 您可以获得该许可的副本：
 *           http://www.apache.org/licenses/LICENSE-2.0
 *           除非适用法律需要或者书面同意，按本许可分发的软件
 *           要按“原样”分发，没有任何形式的，明确或隐含的担保条款。
 *           参见按照本许可控制许可权限及限制的特定语言的许可证。
 *
 *   你可以获得该代码的最新版本：
 *
 *        https://git.oschina.net/Mr_ChenLuYong/screenshot
 *
 *   开源社区的所有人都期待与你的共同维护。
 *
 *
 *   如果你对这些代码还有不理解的地方可以通过最新的文章进行学习：
 *
 *        博客地址：http://blog.csdn.net/csnd_ayo
 *
 *        文章地址：http://blog.csdn.net/csnd_ayo/article/details/70197915
 *
 * 	 期待你提交Bug，欢迎Issues。
 *
*/




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

bool OEScreen::isInit_ = false;
OEScreen::OEScreen(std::shared_ptr<QPixmap> originPainting, QPoint pos, QWidget *parent)
    : QWidget(parent), direction_(NONE), originPoint_(pos),
      isPressed_(false), originPainting_(originPainting) {
    menu_ = new QMenu(this);
    menu_->addAction("完成截图", this, SLOT(onSaveScreen()));
    menu_->addAction("保存", this, SLOT(onSaveScreenOther()));
    menu_->addSeparator();
    menu_->addAction("退出截图", this, SLOT(quitScreenshot()));

    /// 双击即完成
    connect(this, SIGNAL(doubleClick()),
            this, SLOT(onSaveScreen()));

    /// 设置成无边框对话框
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
    /// 开启鼠标实时追踪
    setMouseTracking(true);
    /// 默认隐藏
    hide();
}

OEScreen::DIRECTION OEScreen::getRegion(const QPoint &cursor) {
    if (!isInit_) {
        return NONE;
    }
    OEScreen::DIRECTION ret_dir = NONE;
    // left upper
    QPoint pt_lu = mapToParent(rect().topLeft());
    // right lower
    QPoint pt_rl = mapToParent(rect().bottomRight());

    int x = cursor.x();
    int y = cursor.y();

    /// 获得鼠标当前所处窗口的边界方向
    if(pt_lu.x() + PADDING_ >= x
    && pt_lu.x() <= x
    && pt_lu.y() + PADDING_ >= y
    && pt_lu.y() <= y) {
        // 左上角
        ret_dir = LEFTUPPER;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x >= pt_rl.x() - PADDING_
           && x <= pt_rl.x()
           && y >= pt_rl.y() - PADDING_
           && y <= pt_rl.y()) {
        // 右下角
        ret_dir = RIGHTLOWER;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= pt_lu.x() + PADDING_
           && x >= pt_lu.x()
           && y >= pt_rl.y() - PADDING_
           && y <= pt_rl.y()) {
        // 左下角
        ret_dir = LEFTLOWER;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= pt_rl.x()
           && x >= pt_rl.x() - PADDING_
           && y >= pt_lu.y()
           && y <= pt_lu.y() + PADDING_) {
        // 右上角
        ret_dir = RIGHTUPPER;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= pt_lu.x() + PADDING_
           && x >= pt_lu.x()) {
        // 左边
        ret_dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= pt_rl.x()
            && x >= pt_rl.x() - PADDING_) {
        // 右边
        ret_dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= pt_lu.y()
          && y <= pt_lu.y() + PADDING_){
        // 上边
        ret_dir = UPPER;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= pt_rl.y()
           && y >= pt_rl.y() - PADDING_) {
        // 下边
        ret_dir = LOWER;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        ret_dir = NONE;
        this->setCursor(QCursor(Qt::SizeAllCursor));
    }
    return ret_dir;
}


void OEScreen::contextMenuEvent(QContextMenuEvent *) {
    /// 在鼠标位置弹射出菜单栏
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
            setCursor(QCursor(Qt::SizeAllCursor));
        }
    }
}

void OEScreen::mouseMoveEvent(QMouseEvent * e) {
    QPoint gloPoint = mapToParent(e->pos());
    // left upper
    QPoint pt_lu = mapToParent(rect().topLeft());
    // left lower
    QPoint pt_ll = mapToParent(rect().bottomLeft());
    // right lower
    QPoint pt_rl = mapToParent(rect().bottomRight());
    // right upper
    QPoint pt_ru = mapToParent(rect().topRight());
    if(!isPressed_) {
        /// 检查鼠标鼠标方向
        direction_ = getRegion(gloPoint);

        /// 根据方位判断拖拉对应支点
        switch(direction_) {
        case NONE:
        case RIGHT:
        case RIGHTLOWER:
            originPoint_ = pt_lu;
            break;
        case RIGHTUPPER:
            originPoint_ = pt_ll;
            break;
        case LEFT:
        case LEFTLOWER:
            originPoint_ = pt_ru;
            break;
        case LEFTUPPER:
        case UPPER:
            originPoint_ = pt_rl;
            break;
        case LOWER:
            originPoint_ = pt_lu;
            break;
        }
    }
    else {
        if(direction_ != NONE) {
            const int& global_x = gloPoint.x();
            /// 鼠标进行拖拉拽
            switch(direction_) {
            case LEFT:
                return onMouseChange(global_x, pt_ll.y() + 1);
            case RIGHT:
                return onMouseChange(global_x, pt_rl.y() + 1);
            case UPPER:
                return onMouseChange(pt_lu.x(), gloPoint.y());
            case LOWER:
                return onMouseChange(pt_rl.x() + 1, gloPoint.y());
            case LEFTUPPER:
            case RIGHTUPPER:
            case LEFTLOWER:
            case RIGHTLOWER:
                return onMouseChange(global_x, gloPoint.y());
            default:
                break;
            }
        }
        else {
            /// 窗口的移动
            move(e->globalPos() - movePos_);
            movePos_ = e->globalPos() - pos();
            e->accept();
        }
    }
    currentRect_ = geometry();
}

void OEScreen::moveEvent(QMoveEvent *) {
    emit postionChange(x(), y());
}

void OEScreen::resizeEvent(QResizeEvent *) {
    listMarker_.clear();

    /// 重新计算八个锚点
    // 角点
    listMarker_.push_back(QPoint(0, 0));
    listMarker_.push_back(QPoint(width(), 0));
    listMarker_.push_back(QPoint(0, height()));
    listMarker_.push_back(QPoint(width(), height()));

    // 中点
    listMarker_.push_back(QPoint((width() >> 1), 0));
    listMarker_.push_back(QPoint((width() >> 1), height()));
    listMarker_.push_back(QPoint(0, (height() >> 1)));
    listMarker_.push_back(QPoint(width(), (height() >> 1)));

    emit sizeChange(width(), height());
}

void OEScreen::showEvent(QShowEvent *)
{
    isInit_ = true;
}

void OEScreen::hideEvent(QHideEvent *)
{
    currentRect_ = {};
    movePos_ = {};
    originPoint_ = {};
    isInit_ = false;
}

void OEScreen::enterEvent(QEvent *e) {
    setCursor(Qt::SizeAllCursor);
    QWidget::enterEvent(e);
}

void OEScreen::leaveEvent(QEvent *e) {
    setCursor(Qt::ArrowCursor);
    QWidget::leaveEvent(e);
}

void OEScreen::closeEvent(QCloseEvent *)
{
    isInit_ = false;
}

void OEScreen::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    /// 绘制截屏编辑窗口
    painter.drawPixmap(QPoint(0,0),
       *originPainting_, currentRect_);

    /// 绘制边框线
    QPen pen(QColor(0,174,255),2);
    painter.setPen(pen);
    painter.drawRect(rect());

    /// 绘制八个点
    //改变点的宽度
    pen.setWidth(4);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoints(listMarker_);
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
    /// 把图片放入剪切板
    QClipboard *board = QApplication::clipboard();
    board->setPixmap(originPainting_->copy(currentRect_));
    /// 退出当前截图工具
    quitScreenshot();
}


void OEScreen::quitScreenshot(void) {
    close();
    parentWidget()->close();
}

void OEScreen::onMouseChange(int x, int y) {
    show();
    if (x < 0 || y < 0) {
        return;
    }
    const int& rx = (x >= originPoint_.x()) ? originPoint_.x() : x;
    const int& ry = (y >= originPoint_.y()) ? originPoint_.y() : y;
    const int& rw = abs(x - originPoint_.x());
    const int& rh = abs(y - originPoint_.y());

    /// 改变大小
    currentRect_ = QRect(rx, ry, rw, rh);

    this->setGeometry(currentRect_);
    /// 改变大小后更新父窗口，防止父窗口未及时刷新而导致的问题
    parentWidget()->update();
}
