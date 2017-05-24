#ifndef OEMODELVIEW_H
#define OEMODELVIEW_H

#include <QWidget>
#include <QMap>
#include <QColor>
#include <QPoint>

class OEModelView : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief : 模型种类
    */
    enum MODEL{
        Arrows = 0, /// 箭头
        Rectangle = 1, /// 矩形
        Roundness /// 圆形
    };

private:
    typedef void (OEModelView::*PDRAWFUNC)
                (const QPoint &,const QPoint &, QPainter&);


signals:

public:
    explicit OEModelView(MODEL model = MODEL::Arrows,
                         QWidget *parent = 0);

protected:

    /**
     * @brief : 自绘事件
     */
    virtual void paintEvent(QPaintEvent *);

private:

    /**
     * @brief : 画箭头
     * @param : 箭头起点
     * @param : 箭头终点
     * @param : 画板
     */
    void drawArrows(const QPoint &startPoint,
                    const QPoint &endPoint,
                    QPainter& paiter);
    /**
     * @brief : 画方块
     * @param : 方块起点
     * @param : 方块终点
     * @param : 画板
     */
    void drawRect(const QPoint &startPoint,
                    const QPoint &endPoint,
                    QPainter& paiter);

    /**
     * @brief : 画圆形
     * @param : 圆形起点
     * @param : 圆形终点
     * @param : 画板
     */
    void drawEllipse(const QPoint &startPoint,
                    const QPoint &endPoint,
                    QPainter& paiter);

public slots:

    void onColor(const QColor &color);

private:
    QColor color_;
    PDRAWFUNC drawFunc_;
};


#endif // OEMODELVIEW_H
