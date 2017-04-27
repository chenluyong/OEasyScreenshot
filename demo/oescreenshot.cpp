#include "oescreenshot.h"

#include <QPainter>
#include <QScreen>
#include <QDesktopWidget>
#include <QApplication>
#include <QMouseEvent>
#include <QCursor>
#include <QMutex>
#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include "oeamplifier.h"
#include "oescreen.h"
#include "oerect.h"

OEScreenshot * OEScreenshot::self_ = nullptr;

OEScreenshot::OEScreenshot(QWidget *parent) : QWidget(parent),
    backgroundScreen_(nullptr), originPainting_(nullptr),screenTool_(nullptr)
{
    // 初始化鼠标
    initCursor(":/cursor/cursor.png");
    // 截取屏幕信息
    initGlobalScreen();
    // 初始化鼠标放大器
    initAmplifier();
    // 初始化大小感知器
    initMeasureWidget();
    // 窗口置顶
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    // 全屏窗口
    showFullScreen();
    // 窗口与显示屏对齐
    setGeometry(getScreenRect());
    // 展示窗口
    show();
}

OEScreenshot::~OEScreenshot()
{
    if (backgroundScreen_ != nullptr) {
        delete backgroundScreen_;
        backgroundScreen_ = nullptr;
    }
}

/*
 * 功能：窗口实例
 * 返回：OEScreenshot
 */
OEScreenshot *OEScreenshot::Instance() {
    static QMutex mutex;
    if (!self_) {
       QMutexLocker locker(&mutex);
       if (!self_) {
           self_ = new OEScreenshot;
       }
    }
    return self_;
}

void OEScreenshot::mouseDoubleClickEvent(QMouseEvent *)
{
    emit doubleClick();
}


/*
 * 初始化放大镜 (色彩采集器)
 */
void OEScreenshot::initAmplifier() {

}

void OEScreenshot::initMeasureWidget()
{
    rectTool_ = new OERect(this);
    rectTool_->raise();
}

/*
 * 功能：获得当前屏幕的大小
 */
const QRect &OEScreenshot::getScreenRect() {
    if (!desktopRect_.isEmpty()) {
        return desktopRect_;
    }
    // 获得屏幕个数
    int temp_screen_num = QApplication::screens().size();
    // 获得屏幕大小
    desktopRect_ = QApplication::desktop()->rect();
    if (temp_screen_num != 1) {
        // 多屏幕策略
        const int& temp = desktopRect_.width() -
                (desktopRect_.width() / temp_screen_num);
        // 重新设置矩形
        desktopRect_ = QRect(-temp, 0,
              desktopRect_.width(), desktopRect_.height());
    }
    return desktopRect_;
}

const QPixmap *OEScreenshot::initGlobalScreen() {
    if (backgroundScreen_ != nullptr) {
        return backgroundScreen_;
    }
    // 获得屏幕原画
    const QPixmap* temp_screen = getGlobalScreen();

    // 制作暗色屏幕背景
    QPixmap temp_dim_pix(temp_screen->width(), temp_screen->height());
    temp_dim_pix.fill((QColor(0, 0, 0, 160)));
    backgroundScreen_ = new QPixmap(*temp_screen);
    QPainter p(backgroundScreen_);
    p.drawPixmap(0, 0, temp_dim_pix);

    return backgroundScreen_;
}

/*
 * 获得屏幕的原画
 * 返回：QPixmap* 指针
 */
const QPixmap *OEScreenshot::getGlobalScreen() {
    if (originPainting_ == nullptr) {
        // 截取当前桌面，作为截屏的背景图
        QScreen *screen = QGuiApplication::primaryScreen();
        const QRect& temp_rect = getScreenRect();
        originPainting_ = new QPixmap(screen->grabWindow(0, temp_rect.x(),
                            temp_rect.y(), temp_rect.width(),
                            temp_rect.height()));
    }
    return originPainting_;
}

/*
 * 初始化鼠标
 * 参数：_ico 鼠标图片的资源文件
 */
void OEScreenshot::initCursor(const QString& _ico) {
    if (_ico.isEmpty()) {
        return ;
    }
    QCursor cursor ;
    QPixmap pixmap(_ico) ;
    cursor = QCursor(pixmap, -1, -1);
    setCursor(cursor);
}

OEScreen *OEScreenshot::getScreen(const QPoint &pos) {
    if (screenTool_ == nullptr) {
        screenTool_ = new OEScreen(originPainting_, pos, this);
        // 建立截图器大小关联
        connect (this, SIGNAL(cursorPosChange(int,int)),
                 screenTool_,SLOT(onMouseChange(int,int)));
        connect (this, SIGNAL(doubleClick()),
                 screenTool_,SLOT(onSaveScreen()));
        connect(screenTool_, SIGNAL(sizeChange(int,int)),
                rectTool_, SLOT(onSizeChange(int,int)));
        connect(screenTool_, SIGNAL(postionChange(int,int)),
                rectTool_, SLOT(onPostionChange(int,int)));
        rectTool_->show();
        // 获得截图器当前起始位置
        startPoint_ = pos;
        isScreenShow_ = true;
    }
    return screenTool_;
}

void OEScreenshot::delScreen() {
    if (screenTool_ != nullptr) {
        // 断开信号资源
        disconnect (this, SIGNAL(cursorPosChange(int,int)),
                screenTool_,SLOT(onMouseChange(int,int)));
        disconnect (this, SIGNAL(doubleClick()),
                screenTool_,SLOT(onSaveScreen()));
        disconnect(screenTool_, SIGNAL(sizeChange(int,int)),
                rectTool_, SLOT(onSizeChange(int,int)));
        disconnect(screenTool_, SIGNAL(postionChange(int,int)),
                rectTool_, SLOT(onPostionChange(int,int)));
        rectTool_->hide();
        // 清理工具
        delete screenTool_;
        screenTool_ = nullptr;
        isScreenShow_ = false;
        return;
    }
}


void OEScreenshot::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        getScreen(e->pos());
        return ;
    }
}

void OEScreenshot::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton
        || startPoint_ == e->pos()) {
        if (screenTool_ != nullptr) {
            return delScreen();
        }
        close();
        return ;
    }
    else if (isScreenShow_ == true
             && e->button() == Qt::LeftButton) {
        screenTool_->done();
        isScreenShow_ = false;
    }
    QWidget::mouseReleaseEvent(e);
}

void OEScreenshot::mouseMoveEvent(QMouseEvent *e) {
    if (isScreenShow_) {
        emit cursorPosChange(e->x(), e->y());
    }
    QWidget::mouseMoveEvent(e);
}

void OEScreenshot::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    // 画全屏图
    painter.drawPixmap(0,0,desktopRect_.width(),
             desktopRect_.height(), *backgroundScreen_);
}
