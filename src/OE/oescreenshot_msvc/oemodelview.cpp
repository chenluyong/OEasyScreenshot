#include "oemodelview.h"

#include <QPen>
#include <QPainter>
#include <QPoint>
#include <QDebug>

/// @test : 测试变量
QPoint startPoint_;
QPoint endPoint_;


OEModelView::OEModelView(MODEL model,
        QWidget *parent) : QWidget(parent),
        color_(Qt::red) {
    /// 确定画图样式
    switch (model) {
    case MODEL::Arrows:
    {
        drawFunc_ = &OEModelView::drawArrows;
        break;
    }
    default:
    {
        drawFunc_ = &OEModelView::drawArrows;
    }
    }
}


void OEModelView::paintEvent(QPaintEvent *) {
    QPainter paiter(this);

    /// @test : 测试变量
    startPoint_ = QPoint(width(),height());
    endPoint_ = {};

    /// 绘制图形
    (this->*drawFunc_)(startPoint_, endPoint_, paiter);
}


void OEModelView::drawArrows(const QPoint& startPoint,
                             const QPoint& endPoint,
                             QPainter &paiter) {
    /// 消锯齿
    paiter.setRenderHint(QPainter::Antialiasing, true);
    /// 创建画笔,设置画刷
    QPen pen;
    pen.setColor(color_);
    pen.setWidth(1);
    paiter.setPen(pen);
    paiter.setBrush(color_);


    /// 箭头部分三角形的腰长
    double par = 15.0;
    double slopy = atan2((endPoint.y() - startPoint.y()),
                         (endPoint.x() - startPoint.x()));
    double cos_y = cos(slopy);
    double sin_y = sin(slopy);
    QPoint head_point1 = QPoint(endPoint.x() + int(-par*cos_y - (par / 2.0 * sin_y)),
                           endPoint.y() + int(-par*sin_y + (par / 2.0 * cos_y)));
    QPoint head_point2 = QPoint(endPoint.x() + int(-par*cos_y + (par / 2.0 * sin_y)),
                           endPoint.y() - int(par / 2.0*cos_y + par * sin_y));
    QPoint head_points[3] = { endPoint, head_point1, head_point2 };
    /// 绘制箭头部分
    paiter.drawPolygon(head_points, 3);


    /// 计算箭身部分
    int offset_x = int(par*sin_y / 3);
    int offset_y = int(par*cos_y / 3);
    QPoint body_point1, body_point2;
    body_point1 = QPoint(endPoint.x() + int(-par*cos_y - (par / 2.0*sin_y)) +
                    offset_x, endPoint.y() + int(-par*sin_y + (par / 2.0*cos_y)) - offset_y);
    body_point2 = QPoint(endPoint.x() + int(-par*cos_y + (par / 2.0*sin_y) - offset_x),
                    endPoint.y() - int(par / 2.0*cos_y + par*sin_y) + offset_y);
    QPoint body_points[3] = { startPoint, body_point1, body_point2 };
    /// 绘制箭身部分
    paiter.drawPolygon(body_points, 3);

}
void OEModelView::onColor(const QColor &color) {
    color_ = color;
}
