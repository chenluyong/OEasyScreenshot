/*
版权所有 [2017] [瓯裔]

   根据 Apache 许可证 2.0 版（以下简称“许可证”）授权；
   除非遵守本许可，否则您不能使用这个文件。
   您可以获得该许可的副本：

        http://www.apache.org/licenses/LICENSE-2.0


   除非适用法律需要或者书面同意，按本许可分发的软件
   要按“原样”分发，没有任何形式的，明确或隐含的担保条款。
   参见按照本许可控制许可权限及限制的特定语言的许可证。

   你可以获得该代码的最新版本：

        https://git.oschina.net/Mr_ChenLuYong/screenshot

   开源社区的所有人都期待与你的共同维护。
*/


#include "oescreenshot.h"

#include <QPainter>
#include <QScreen>
#include <QDesktopWidget>
#include <QApplication>
#include <QMouseEvent>
#include <QCursor>
#include <QMutex>
#include <QTimer>
#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include <windows.h>

#include "oeamplifier.h"
#include "oescreen.h"
#include "oerect.h"
#include "oecommonhelper.h"

OEScreenshot * OEScreenshot::self_ = nullptr;

OEScreenshot::OEScreenshot(QWidget *parent) : QWidget(parent),isLeftPressed_ (false),
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
    // 全屏窗口
    showFullScreen();
    // 窗口与显示屏对齐
    setGeometry(getScreenRect());
    // 霸道置顶
    onEgoistic();
    // 开启鼠标实时追踪
    setMouseTracking(true);
    // 展示窗口
    show();
}

OEScreenshot::~OEScreenshot(void)
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
OEScreenshot *OEScreenshot::Instance(void) {
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
void OEScreenshot::initAmplifier(void) {
    amplifierTool_ = new OEAmplifier(originPainting_, this);
    connect(this,SIGNAL(cursorPosChange(int,int)),
            amplifierTool_, SLOT(onPostionChange(int,int)));
    amplifierTool_->onPostionChange(x(), y());
    amplifierTool_->show();
    amplifierTool_->raise();
}

void OEScreenshot::initMeasureWidget(void)
{
    rectTool_ = new OERect(this);
    rectTool_->raise();
}

/*
 * 功能：获得当前屏幕的大小
 */
const QRect &OEScreenshot::getScreenRect(void) {
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

const QPixmap *OEScreenshot::initGlobalScreen(void) {
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
const QPixmap *OEScreenshot::getGlobalScreen(void) {
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
void OEScreenshot::onEgoistic(void)
{
    // 窗口置顶
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
void OEScreenshot::initCursor(const QString& _ico) {
    if (_ico.isEmpty()) {
        return ;
    }
    QCursor cursor ;
    QPixmap pixmap(_ico) ;
    cursor = QCursor(pixmap, -1, -1);
    setCursor(cursor);
}

OEScreen *OEScreenshot::createScreen(const QPoint &pos) {
    if (screenTool_ == nullptr) {
        screenTool_ = new OEScreen(originPainting_, pos, this);
        connect (this, SIGNAL(cursorPosChange(int,int)),
                 screenTool_,SLOT(onMouseChange(int,int)));
        // 建立主界面双击保存信号关联
        connect (this, SIGNAL(doubleClick()),
                 screenTool_,SLOT(onSaveScreen()));
        // 建立截图器大小关联
        connect(screenTool_, SIGNAL(sizeChange(int,int)),
                rectTool_, SLOT(onSizeChange(int,int)));
        connect(screenTool_, SIGNAL(sizeChange(int,int)),
                amplifierTool_, SLOT(onSizeChange(int,int)));
        // 建立截图器与感知器的位置关联
        connect(screenTool_, SIGNAL(postionChange(int,int)),
                rectTool_, SLOT(onPostionChange(int,int)));

        // 获得截图器当前起始位置
        startPoint_ = pos;
        isLeftPressed_ = true;
    }
    return screenTool_;
}

void OEScreenshot::destroyScreen() {
    if (screenTool_ != nullptr) {
        // 断开信号资源
        disconnect (this, SIGNAL(doubleClick()),
                screenTool_,SLOT(onSaveScreen()));
        disconnect(screenTool_, SIGNAL(sizeChange(int,int)),
                rectTool_, SLOT(onSizeChange(int,int)));
        disconnect(screenTool_, SIGNAL(postionChange(int,int)),
                rectTool_, SLOT(onPostionChange(int,int)));
        // 清理工具
        delete screenTool_;
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
        if (screenTool_ != nullptr) {
            rectTool_->hide();
            amplifierTool_->onPostionChange(x(), y());
            amplifierTool_->show();
            return destroyScreen();
        }
        close();
        return ;
    }
    else if (isLeftPressed_ == true
             && e->button() == Qt::LeftButton) {
        // 选择窗口选区
        if (startPoint_ == e->pos()
            && !windowRect_.isEmpty()) {
            screenTool_->setGeometry(windowRect_);
            screenTool_->show();
            windowRect_ = {};
        }
        // 断开鼠标移动的信号
        disconnect (this, SIGNAL(cursorPosChange(int,int)),
                screenTool_,SLOT(onMouseChange(int,int)));
        // 隐藏放大器
        amplifierTool_->hide();
        // 断开截图器的大小修改信号
        disconnect (screenTool_, SIGNAL(sizeChange(int,int)),
                amplifierTool_,SLOT(onSizeChange(int,int)));
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
        // 霸道置顶
        onEgoistic();

        // 获取当前鼠标选中的窗口
        ::EnableWindow((HWND)winId(), FALSE);
        OECommonHelper::getCurrentWindowFromCursor(windowRect_);
        QPoint temp_pt = mapFromGlobal(QPoint(windowRect_.x(), windowRect_.y()));
        windowRect_ = QRect(temp_pt.x(), temp_pt.y(),
                            windowRect_.width(), windowRect_.height());
        ::EnableWindow((HWND)winId(), TRUE);
        amplifierTool_->onSizeChange(windowRect_.width(),windowRect_.height());
        emit findChildWind(windowRect_);
        update();
    }
    QWidget::mouseMoveEvent(e);
}

void OEScreenshot::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    // 画全屏图
    painter.drawPixmap(0,0,desktopRect_.width(),
             desktopRect_.height(), *backgroundScreen_);

    if (!windowRect_.isEmpty()) {
        // 绘制选区
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

void OEScreenshot::keyPressEvent(QKeyEvent *e) {
    // Esc 键退出截图;
    if (e->key() == Qt::Key_Escape) {
        close();
    }
    else {
        e->ignore();
    }
}
