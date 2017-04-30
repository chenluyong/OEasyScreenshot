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



#include "oeamplifier.h"


#include <QPixmap>
#include <QPainter>

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif


#include "oecommonhelper.h"

OEAmplifier::OEAmplifier(std::shared_ptr<QPixmap> originPainting, QWidget *parent) :
    QWidget(parent), originPainting_(originPainting) {
    /// 设置成无边框对话框
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
    /// 开启鼠标实时追踪
    setMouseTracking(true);

    /// 设置默认大小
    sideLength_ = 122 * OECommonHelper::getWindowHeightMultiplyingPower();
    imageHeight_ = 90 * OECommonHelper::getWindowHeightMultiplyingPower();
    setFixedSize(sideLength_,sideLength_);

    /// 默认隐藏
    hide();
}

void OEAmplifier::onSizeChange(int w, int h) {
    screenSize_ = QSize(w, h);
}

void OEAmplifier::onPostionChange(int x, int y) {
    cursorPoint_ = QPoint(x, y);
    raise();
    int dest_x = x + 4;
    int dest_y = y + 26;

    /// 超出屏幕检测
    const QSize& parent_size = parentWidget()->size();
    if (dest_y + height() > parent_size.height()) {
        dest_y = y - 26 - height();
    }
    if (dest_x + width() > parent_size.width()) {
        dest_x = x - 4 - width();
    }

    move(dest_x, dest_y);
}



/// 绘制鼠标拖拽时选区矩形的右下顶点的放大图;
void OEAmplifier::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    /// 绘制背景
    painter.fillRect(rect(), QColor(0, 0, 0, 160));

    QPixmap endPointImage;
    /// 绘制放大图;
    const QSize& parent_size = parentWidget()->size();
    /**
     * @bug   : 在屏幕边缘绘制放大图时会出现图片拉伸
     *          这里暂时做了边缘检测，若是屏幕边缘则不进行放大图的绘制，和QQ截图的采取方式是一致的。
     *
     * @marker: 颜色还是照样识别，但是局部放大的效果暂时禁用
     *
     * @note  : 解决方法，可以发现边缘时，将不能放大的地方，不描绘，或填充黑色，以避免图片被非预期的拉伸问题。
     */
    if ((cursorPoint_.x() + 15 < parent_size.width() && cursorPoint_.x() - 15 > 0)
      && (cursorPoint_.y() + 11 < parent_size.height() && cursorPoint_.y() - 11 > 0)) {
        endPointImage = originPainting_->
                copy(QRect(cursorPoint_.x() - 15,
                     cursorPoint_.y() - 11, 30, 22))
                .scaled(sideLength_, imageHeight_);
        painter.drawPixmap(0,0, endPointImage);
    }
    else {
        endPointImage = originPainting_->
                copy(QRect(cursorPoint_.x() - 15,
                     cursorPoint_.y() - 11, 30, 22));
    }


    /// 绘制十字
    painter.setPen(QPen(QColor(0, 180, 255 , 180), 4));
    // 竖线;
    painter.drawLine(QPoint(sideLength_ >> 1, 0),
                     QPoint(sideLength_ >> 1,
                            imageHeight_ - 4));
    // 横线;
    painter.drawLine(QPoint(0, imageHeight_ >> 1),
                     QPoint(sideLength_,
                            imageHeight_ >> 1));

    /// 绘制大图内边框
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(2,2,width()-4, imageHeight_-4);

    /// 绘制外边框
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRect(0,0,width()-1,height()-1);

    /// 当前选中矩形的宽高信息;
    QString select_screen_info = QString("%1×%2")
            .arg(screenSize_.width()).arg(screenSize_.height());

    /// 当前鼠标像素值的RGB信息
    QImage image = originPainting_->toImage();
    QColor cursor_pixel = image.pixel(cursorPoint_);
    QString select_pt_rgb = QString("RGB:(%1,%2,%3)")
                                    .arg(cursor_pixel.red())
                                    .arg(cursor_pixel.green())
                                    .arg(cursor_pixel.blue());

    /// 绘制坐标轴相关数据
    painter.setPen(Qt::white);
    painter.drawText(QPoint(6, imageHeight_+14),select_screen_info);
    painter.drawText(QPoint(6, imageHeight_+27),select_pt_rgb);
}
