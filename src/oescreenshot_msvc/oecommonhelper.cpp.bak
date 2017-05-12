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


#include "oecommonhelper.h"

#include <QFile>
#include <QTranslator>
#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>

#include <windows.h>

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif


#define WINDOW_BASESIZE_WIDTH (1920)
#define WINDOW_BASESIZE_HEIGHT (1080)

float OECommonHelper::widthMultiplyingPower_ = 0;
float OECommonHelper::heightMultiplyingPower_ = 0;

void OECommonHelper::setStyle(const QString &style) {
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

void OECommonHelper::setLanguagePack(const QString &language) {
    // 加载中文包
    QTranslator translator;
    translator.load(language);
    qApp->installTranslator(&translator);
}

void OECommonHelper::moveCenter(QWidget *widget, QRect parentRect) {
    if (parentRect.isEmpty()) {
        parentRect = QApplication::desktop()->rect();
    }
    widget->move (((parentRect.width() - widget->width()) >> 1),
          ((parentRect.height() - widget->height()) >> 1));
}

const float &OECommonHelper::getWindowWidthMultiplyingPower() {
    if (widthMultiplyingPower_ == 0) {
        upWindowSizeMultiplyingPower();
    }
    return widthMultiplyingPower_;
}

const float & OECommonHelper::getWindowHeightMultiplyingPower() {
    if (heightMultiplyingPower_ == 0) {
        upWindowSizeMultiplyingPower();
    }
    return heightMultiplyingPower_;
}

void OECommonHelper::upWindowSizeMultiplyingPower() {
   QSize temp_size = QApplication::desktop()->size();
   widthMultiplyingPower_ = (float)temp_size.width()
           / (float)WINDOW_BASESIZE_WIDTH;
   heightMultiplyingPower_ = (float)temp_size.height()
           / (float)WINDOW_BASESIZE_HEIGHT;
}

bool OECommonHelper::getSmallestWindowFromCursor(QRect& out_rect) {
    HWND hwnd;
    POINT pt;
    // 获得当前鼠标位置
    ::GetCursorPos(&pt);
    // 获得当前位置桌面上的子窗口
    hwnd = ::ChildWindowFromPointEx(::GetDesktopWindow(), pt, CWP_SKIPDISABLED | CWP_SKIPINVISIBLE);
    if (hwnd != NULL) {
        HWND temp_hwnd;
        temp_hwnd = hwnd;
        while (true) {
            ::GetCursorPos(&pt);
            ::ScreenToClient(temp_hwnd, &pt);
            temp_hwnd = ::ChildWindowFromPointEx(temp_hwnd, pt, CWP_SKIPINVISIBLE);
            if (temp_hwnd == NULL || temp_hwnd == hwnd)
                break;
            hwnd = temp_hwnd;
        }
        RECT temp_window;
        ::GetWindowRect(hwnd, &temp_window);
        out_rect.setRect(temp_window.left,temp_window.top,
                         temp_window.right - temp_window.left,
                         temp_window.bottom - temp_window.top);
        return true;
    }
    return false;
}

bool OECommonHelper::getCurrentWindowFromCursor(QRect &out_rect)
{
    HWND hwnd;
    POINT pt;
    // 获得当前鼠标位置
    ::GetCursorPos(&pt);
    // 获得当前位置桌面上的子窗口
    hwnd = ::ChildWindowFromPointEx(::GetDesktopWindow(), pt, CWP_SKIPDISABLED | CWP_SKIPINVISIBLE);
    if (hwnd != NULL) {
        RECT temp_window;
        ::GetWindowRect(hwnd, &temp_window);
        out_rect.setRect(temp_window.left, temp_window.top,
                         temp_window.right - temp_window.left,
                         temp_window.bottom - temp_window.top);
        return true;
    }
    return false;
}
