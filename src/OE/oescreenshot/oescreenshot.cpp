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

#include "oescreenshot.h"


#include <QDesktopWidget>
#include <QApplication>
#include <QMouseEvent>
#include <QFileDialog>
#include <QClipboard>
#include <QDateTime>
#include <QPainter>
#include <QScreen>
#include <QCursor>
#include <QMutex>
#include <QMenu>
#include <QPen>
#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include <windows.h>

#include "oeamplifier.h"
#include "oecommonhelper.h"


/// 鼠标按钮图片的十六进制数据
static const unsigned char uc_mouse_image[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,  0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52
    ,0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x2D,  0x08, 0x06, 0x00, 0x00, 0x00, 0x52, 0xE9, 0x60
    ,0xA2, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59,  0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B
    ,0x13, 0x01, 0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00,  0x01, 0x40, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85
    ,0xED, 0xD5, 0x21, 0x6E, 0xC3, 0x30, 0x14, 0xC6,  0xF1, 0xFF, 0x9B, 0xC6, 0x36, 0x30, 0x38, 0xA9
    ,0x05, 0x01, 0x05, 0x81, 0x05, 0x03, 0x39, 0xCA,  0x60, 0x8F, 0xD2, 0x03, 0xEC, 0x10, 0x3B, 0x46
    ,0xC1, 0xC0, 0xC6, 0x0A, 0x3B, 0x96, 0xB1, 0x80,  0x82, 0xC1, 0x56, 0x2A, 0xFF, 0x06, 0xE2, 0x36
    ,0x75, 0x9A, 0xB4, 0xCA, 0xEC, 0x4E, 0x9A, 0xE4,  0x2F, 0xB2, 0x42, 0x22, 0xFF, 0xF2, 0xFC, 0x9C
    ,0x18, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52,  0x52, 0x52, 0x52, 0xFE, 0x55, 0xE4, 0xC6, 0xA0
    ,0xDC, 0xC4, 0x71, 0x87, 0xC1, 0xC1, 0x68, 0x01,  0xCC, 0x06, 0xC2, 0x51, 0xD0, 0x29, 0xB0, 0x18
    ,0x00, 0xDF, 0xC6, 0x40, 0x33, 0x37, 0x84, 0x30,  0x4C, 0x80, 0x85, 0xCE, 0x7B, 0x2E, 0x2A, 0x91
    ,0x84, 0x24, 0xBE, 0x25, 0xDE, 0x25, 0x5E, 0x2F,  0x6E, 0xAE, 0xD0, 0x37, 0x92, 0x10, 0xF0, 0x09
    ,0x54, 0x40, 0xE9, 0xEE, 0x15, 0xC6, 0xA2, 0x77,  0xFE, 0xE0, 0xE5, 0x85, 0x8F, 0x16, 0x58, 0xDF
    ,0x35, 0x06, 0x5B, 0xD3, 0xB9, 0xD4, 0x11, 0xD0,  0xA5, 0x8F, 0xDE, 0x57, 0x75, 0x83, 0x73, 0x50
    ,0x06, 0xF6, 0x72, 0x0A, 0x47, 0x40, 0x57, 0x0D,  0x38, 0xDE, 0xC0, 0x04, 0x6F, 0x68, 0x05, 0x36
    ,0xF5, 0xE1, 0x08, 0x3D, 0xCD, 0xEA, 0xEA, 0x5A,  0xD8, 0xBE, 0x5A, 0x46, 0xB0, 0x05, 0x1E, 0xAC
    ,0xF1, 0xC2, 0xD1, 0xCC, 0x01, 0x6D, 0x74, 0x02,  0xDB, 0x3B, 0xBF, 0xD3, 0x73, 0x07, 0x87, 0x2F
    ,0xEF, 0x53, 0x07, 0x38, 0x82, 0x2F, 0xF6, 0xFB,  0xB8, 0x81, 0x73, 0x41, 0x69, 0x28, 0x3A, 0x7A
    ,0x5C, 0xDD, 0x73, 0xCF, 0x3A, 0x86, 0xA3, 0x05,  0x87, 0xEA, 0xCC, 0x60, 0xA1, 0x06, 0x75, 0x89
    ,0xFE, 0x77, 0x92, 0x76, 0x68, 0x23, 0xEF, 0x88,  0xD3, 0x4C, 0xA8, 0x10, 0x7A, 0xD4, 0xEF, 0x8E
    ,0xBE, 0x8B, 0x68, 0x79, 0x3A, 0xB1, 0x72, 0xE1,  0xAE, 0xBC, 0x13, 0x0D, 0xDE, 0xBD, 0x3D, 0xF3
    ,0x08, 0x15, 0xD4, 0xDF, 0x4C, 0x06, 0x36, 0xF7,  0x9E, 0x09, 0xED, 0xE9, 0x99, 0x97, 0x3E, 0x42
    ,0xFF, 0x30, 0x42, 0x4B, 0xA1, 0x8D, 0xD8, 0xE9,  0x2A, 0xBD, 0xED, 0x41, 0x25, 0x2A, 0x89, 0x37
    ,0x1F, 0xBD, 0xEA, 0x61, 0x8B, 0x5F, 0xDD, 0xC1,  0xFA, 0x01, 0xD8, 0xA3, 0x8F, 0xFB, 0xCA, 0x70
    ,0x16, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,  0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};



OEScreenshot * OEScreenshot::self_ = nullptr;
bool OEScreenshot::isActivity_ = false;
bool OEScreen::isInit_ = false;

OEScreenshot::OEScreenshot(QWidget *parent) : QWidget(parent),
    isLeftPressed_ (false), backgroundScreen_(nullptr),
    originPainting_(nullptr), screenTool_(nullptr) {
    /// 初始化鼠标
    initCursor();
    /// 截取屏幕信息
    initGlobalScreen();
    /// 初始化鼠标放大器
    initAmplifier();
    /// 初始化大小感知器
    initMeasureWidget();
    /// 全屏窗口
    showFullScreen();
    /// 窗口与显示屏对齐
    setGeometry(getScreenRect());
    /// 霸道置顶
    onEgoistic();
    /// 开启鼠标实时追踪
    setMouseTracking(true);
    /// 更新鼠标的位置
    emit cursorPosChange(cursor().pos().x(), cursor().pos().y());
    /// 更新鼠标区域窗口
    updateMouse();
    /// 展示窗口
    show();
}

OEScreenshot::~OEScreenshot(void) {
}

/**
 * @brief：窗口实例
 * @return：OEScreenshot
 */
OEScreenshot *OEScreenshot::Instance(void) {
    if (!isActivity_ && self_) {
        destroy();
    }
    static QMutex mutex;
    if (!self_) {
       QMutexLocker locker(&mutex);
       if (!self_) {
           isActivity_ = true;
           self_ = new OEScreenshot;
       }
    }
    return self_;
}

void OEScreenshot::destroy(void) {
    if (!isActivity_ && self_) {
        delete self_;
        self_ = nullptr;
    }
}

void OEScreenshot::hideEvent(QHideEvent *) {
    isActivity_ = false;
}


void OEScreenshot::closeEvent(QCloseEvent *) {
    isActivity_ = false;
}

void OEScreenshot::mouseDoubleClickEvent(QMouseEvent *) {
    emit doubleClick();
}


/**
 * 初始化放大镜 (色彩采集器)
 */
void OEScreenshot::initAmplifier(std::shared_ptr<QPixmap> originPainting) {
    std::shared_ptr<QPixmap>  temp_pm = originPainting;
    if (temp_pm == nullptr) {
        temp_pm = originPainting_;
    }
    amplifierTool_.reset(new OEAmplifier(temp_pm, this));
    connect(this,SIGNAL(cursorPosChange(int,int)),
            amplifierTool_.get(), SLOT(onPostionChange(int,int)));
    amplifierTool_->show();
    amplifierTool_->raise();
}

void OEScreenshot::initMeasureWidget(void)
{
    rectTool_.reset(new OERect(this));
    rectTool_->raise();
}

/**
 * 功能：获得当前屏幕的大小
 */
const QRect &OEScreenshot::getScreenRect(void) {
    if (!desktopRect_.isEmpty()) {
        return desktopRect_;
    }
    /// 兼容多个屏幕的问题
    desktopRect_ = QRect(QApplication::desktop()->pos(),
          QApplication::desktop()->size());
    return desktopRect_;
}

std::shared_ptr<QPixmap> OEScreenshot::initGlobalScreen(void) {
    if (backgroundScreen_.get() != nullptr) {
        return backgroundScreen_;
    }
    /// 获得屏幕原画
    std::shared_ptr<QPixmap> temp_screen = getGlobalScreen();

    /// 制作暗色屏幕背景
    QPixmap temp_dim_pix(temp_screen->width(), temp_screen->height());
    temp_dim_pix.fill((QColor(0, 0, 0, 160)));
    backgroundScreen_.reset(new QPixmap(*temp_screen));
    QPainter p(backgroundScreen_.get());
    p.drawPixmap(0, 0, temp_dim_pix);

    return backgroundScreen_;
}

/*
 * 获得屏幕的原画
 * 返回：QPixmap* 指针
 */
std::shared_ptr<QPixmap> OEScreenshot::getGlobalScreen(void) {
    if (originPainting_.get() == nullptr) {
        /// 截取当前桌面，作为截屏的背景图
        QScreen *screen = QGuiApplication::primaryScreen();
        const QRect& temp_rect = getScreenRect();
        originPainting_.reset(new QPixmap(screen->grabWindow(0, temp_rect.x(),
                            temp_rect.y(), temp_rect.width(),
                            temp_rect.height())));
    }
    return originPainting_;
}
void OEScreenshot::onEgoistic(void)
{
    /// 窗口置顶
#ifdef Q_OS_WIN32
    SetWindowPos((HWND)this->winId(),HWND_TOPMOST,this->pos().x(),this->pos().y(),this->width(),this->height(),SWP_SHOWWINDOW);
#else
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
#endif
}

/*
 * 初始化鼠标
 * 参数：_ico 鼠标图片的资源文件
 */
void OEScreenshot::initCursor(const QString& ico) {
    QPixmap pixmap;
    if (ico.isEmpty()) {
        pixmap.loadFromData(uc_mouse_image, sizeof(uc_mouse_image));
    }
    else {
        pixmap.load(ico);
    }
    QCursor cursor;
    cursor = QCursor(pixmap, 15, 23);
    setCursor(cursor);
}

std::shared_ptr<OEScreen> OEScreenshot::createScreen(const QPoint &pos) {
    if (screenTool_.get() == nullptr) {
        /// 创建截图器
        screenTool_.reset(new OEScreen(originPainting_, pos, this));
        /// 建立信号连接
        connect (this, SIGNAL(cursorPosChange(int,int)),
                 screenTool_.get(),SLOT(onMouseChange(int,int)));
        /// 建立主界面双击保存信号关联
        connect (this, SIGNAL(doubleClick()),
                 screenTool_.get(),SLOT(onSaveScreen()));
        /// 建立截图器大小关联
        connect(screenTool_.get(), SIGNAL(sizeChange(int,int)),
                rectTool_.get(), SLOT(onSizeChange(int,int)));
        connect(screenTool_.get(), SIGNAL(sizeChange(int,int)),
                amplifierTool_.get(), SLOT(onSizeChange(int,int)));
        /// 建立截图器与感知器的位置关联
        connect(screenTool_.get(), SIGNAL(postionChange(int,int)),
                rectTool_.get(), SLOT(onPostionChange(int,int)));

        /// 获得截图器当前起始位置
        startPoint_ = pos;
        isLeftPressed_ = true;
    }
    return screenTool_;
}

void OEScreenshot::destroyScreen() {
    if (screenTool_.get() != nullptr) {
        /// 断开信号资源
        disconnect (this, SIGNAL(doubleClick()),
                screenTool_.get(),SLOT(onSaveScreen()));
        disconnect(screenTool_.get(), SIGNAL(sizeChange(int,int)),
                rectTool_.get(), SLOT(onSizeChange(int,int)));
        disconnect(screenTool_.get(), SIGNAL(postionChange(int,int)),
                rectTool_.get(), SLOT(onPostionChange(int,int)));
        /// 清理工具
        screenTool_.reset();
        screenTool_ = nullptr;
        isLeftPressed_ = false;
        update();
        return;
    }
}

void OEScreenshot::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        createScreen(e->pos());
        return ;
    }
}

void OEScreenshot::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton) {
        if (screenTool_.get() != nullptr) {
            rectTool_->hide();
            amplifierTool_->onPostionChange(e->x(), e->y());
            amplifierTool_->show();
            /// 更新当前鼠标选中的窗口
            updateMouse();
            return destroyScreen();
        }
        close();
        return ;
    }
    else if (isLeftPressed_ == true
             && e->button() == Qt::LeftButton) {
        /// 选择窗口选区
        if (startPoint_ == e->pos()
            && !windowRect_.isEmpty()) {
            screenTool_->setGeometry(windowRect_);
            screenTool_->show();
            windowRect_ = {};
        }
        /// 断开鼠标移动的信号
        disconnect (this, SIGNAL(cursorPosChange(int,int)),
                screenTool_.get(),SLOT(onMouseChange(int,int)));
        /// 隐藏放大器
        amplifierTool_->hide();
        /// 断开截图器的大小修改信号
        disconnect (screenTool_.get(), SIGNAL(sizeChange(int,int)),
                amplifierTool_.get(),SLOT(onSizeChange(int,int)));
        isLeftPressed_ = false;
    }
    QWidget::mouseReleaseEvent(e);
}

void OEScreenshot::mouseMoveEvent(QMouseEvent *e) {
    emit cursorPosChange(e->x(), e->y());
    if (isLeftPressed_) {
        amplifierTool_->raise();
        windowRect_ = {};
        update();
    }
    else if (isLeftPressed_ == false
             && false == OEScreen::state()){
        /// 霸道置顶
        onEgoistic();

        /// 更新当前鼠标选中的窗口
        updateMouse();
    }
    QWidget::mouseMoveEvent(e);
}

void OEScreenshot::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    /// 画全屏图
    painter.drawPixmap(0,0,desktopRect_.width(),
             desktopRect_.height(), *backgroundScreen_);

    if (!windowRect_.isEmpty()) {
        /// 绘制选区
        QPen pen = painter.pen();
        pen.setColor(QColor(0,175,255));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(windowRect_.x(),windowRect_.y(),
                         windowRect_.width(),windowRect_.height());
        painter.drawPixmap(QPoint(windowRect_.x(),windowRect_.y()),
           *originPainting_, windowRect_);
    }
}

void OEScreenshot::updateMouse(void) {
    /// 获取当前鼠标选中的窗口
    ::EnableWindow((HWND)winId(), FALSE);
    /// @marker: 只更新一次,可以修复用户误操作导致的查找窗口与识别界面窗口不一致.
    OECommonHelper::getSmallestWindowFromCursor(windowRect_);
    QPoint temp_pt = mapFromGlobal(QPoint(windowRect_.x(), windowRect_.y()));
    windowRect_ = QRect(temp_pt.x(), temp_pt.y(),
                        windowRect_.width(), windowRect_.height());
    ::EnableWindow((HWND)winId(), TRUE);
    amplifierTool_->onSizeChange(windowRect_.width(),windowRect_.height());
    emit findChildWind(windowRect_);
    update();
}

void OEScreenshot::keyPressEvent(QKeyEvent *e) {
    /// Esc 键退出截图;
    if (e->key() == Qt::Key_Escape) {
        close();
    }
    else {
        e->ignore();
    }

}



///////////////////////////////////////////////////////////




OERect::OERect(QWidget *parent) : QWidget(parent) {

    /// 设置感知器默认大小
    setFixedSize(95 * OECommonHelper::getWindowHeightMultiplyingPower(),
                 20 * OECommonHelper::getWindowHeightMultiplyingPower());

    /// 填充默认背景
    backgroundPixmap_.reset(new QPixmap(width(),height()));
    backgroundPixmap_->fill((QColor(8, 8, 8, 160)));

    /// 默认隐藏
    hide();
}


void OERect::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(rect(),*backgroundPixmap_);
    painter.setPen(QPen(QColor(Qt::white)));
    painter.drawText(rect(), Qt::AlignCenter, info_);
}

void OERect::onPostionChange(int x, int y) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    const int& ry = y - height() - 1;
    if (ry < 0) {
        this->raise();
    }
    move(x, ((ry < 0) ? y : ry));
    show();
}

void OERect::onSizeChange(int w, int h) {
    info_ = QString("%1 × %2").arg(w).arg(h);
}




///////////////////////////////////////////////////////////





OEScreen::OEScreen(std::shared_ptr<QPixmap> originPainting, QPoint pos, QWidget *parent)
    : QWidget(parent), direction_(NONE), originPoint_(pos),
      isPressed_(false), originPainting_(originPainting) {
    menu_ = new QMenu(this);
    menu_->addAction(QStringLiteral("完成截图"), this, SLOT(onSaveScreen()));
    menu_->addAction(QStringLiteral("保存"), this, SLOT(onSaveScreenOther()));
    menu_->addSeparator();
    menu_->addAction(QStringLiteral("退出截图"), this, SLOT(quitScreenshot()));

    /// 双击即完成
    connect(this, SIGNAL(doubleClick()),
            this, SLOT(onSaveScreen()));

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
        /// @bug :这里可能存在问题, 不应当使用globalPos
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
#ifndef QT_NO_DEBUG
            qDebug() << "OEScreen::" << __FUNCTION__ << "call onMouseChange()";
#endif
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
            /// @bug :这里可能存在问题, 不应当使用globalPos
            move(e->globalPos() - movePos_);
            movePos_ = e->globalPos() - pos();
#ifndef QT_NO_DEBUG
            qDebug() << "OEScreen::" << __FUNCTION__ << pos();
#endif
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

void OEScreen::showEvent(QShowEvent *) {
    isInit_ = true;
}

void OEScreen::hideEvent(QHideEvent *) {
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
    QString file_name = QDateTime::currentDateTime().
            toString(QStringLiteral("CSDN博客_瓯裔_yyyy-MM-dd-HH-mm-ss"));
    return file_name;
}


void OEScreen::onSaveScreenOther(void) {

    QString fileName = QFileDialog::getSaveFileName(this,
                              QStringLiteral("保存图片"),
                              getFileName(), "JPEG Files (*.jpg)");

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


extern "C" void OEScreenshot(void) {
    OEScreenshot::Instance();
}
