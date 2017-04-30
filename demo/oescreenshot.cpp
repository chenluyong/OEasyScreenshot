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

OEScreenshot::OEScreenshot(QWidget *parent) : QWidget(parent),isLeftPressed_ (false),
    backgroundScreen_(nullptr), originPainting_(nullptr),screenTool_(nullptr)
{
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
    /// 展示窗口
    show();
}

OEScreenshot::~OEScreenshot(void)
{
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

void OEScreenshot::hideEvent(QHideEvent *)
{
    isActivity_ = false;
}


void OEScreenshot::closeEvent(QCloseEvent *)
{
    isActivity_ = false;
}

void OEScreenshot::mouseDoubleClickEvent(QMouseEvent *)
{
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
    amplifierTool_->onPostionChange(x(), y());
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
    /// 获得屏幕个数
    int temp_screen_num = QApplication::screens().size();
    /// 获得屏幕大小
    desktopRect_ = QApplication::desktop()->rect();
    if (temp_screen_num != 1) {
        /// 多屏幕策略
        const int& temp = desktopRect_.width() -
                (desktopRect_.width() / temp_screen_num);
        /// 重新设置矩形
        desktopRect_ = QRect(-temp, 0,
              desktopRect_.width(), desktopRect_.height());
    }
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
    cursor = QCursor(pixmap, -1, -1);
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
            amplifierTool_->onPostionChange(x(), y());
            amplifierTool_->show();
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

        /// 获取当前鼠标选中的窗口
        ::EnableWindow((HWND)winId(), FALSE);
        OECommonHelper::getSmallestWindowFromCursor(windowRect_);
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

void OEScreenshot::keyPressEvent(QKeyEvent *e) {
    /// Esc 键退出截图;
    if (e->key() == Qt::Key_Escape) {
        close();
    }
    else {
        e->ignore();
    }

}

void OEScreenshot::keyReleaseEvent(QKeyEvent *)
{

}
