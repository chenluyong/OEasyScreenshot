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

    void drawArrows(const QPoint &startPoint,
                    const QPoint &endPoint,
                    QPainter& paiter);

public slots:

    void onColor(const QColor &color);

private:
    QColor color_;
    PDRAWFUNC drawFunc_;
    /// @bug  : 莫名，开启此处变量的声明，程序就会崩溃。
//    QPoint ssPoint331_;
//    QPoint esoint233_;
};


#endif // OEMODELVIEW_H
