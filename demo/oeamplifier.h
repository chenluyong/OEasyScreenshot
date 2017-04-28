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


#ifndef OEAMPLIFIER_H
#define OEAMPLIFIER_H

#include <QWidget>

class OEAmplifier : public QWidget
{
    Q_OBJECT
public:
    explicit OEAmplifier(QPixmap* originPainting, QWidget *parent = 0);

signals:

public slots:

    void onSizeChange(int w, int h);

    void onPostionChange(int x, int y);

protected:

    virtual void paintEvent(QPaintEvent *);

private:


    QSize parentSize_;
    QSize screenSize_;
    QPoint cursorPoint_;
    int sideLength_;
    int imageHeight_;
    // 屏幕原画
    QPixmap *originPainting_;

};

#endif // OEAMPLIFIER_H
