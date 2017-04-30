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




#include "oerect.h"
#include <QPainter>
#ifndef QT_NO_DEBUG
#include <QDebug>
#endif
#include "oecommonhelper.h"

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
