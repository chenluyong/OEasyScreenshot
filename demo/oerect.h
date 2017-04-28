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


#ifndef OERECT_H
#define OERECT_H

#include <QWidget>
#include <QRect>

class OERect : public QWidget
{
    Q_OBJECT

signals:


public:

    explicit OERect(QWidget *parent = 0);

protected:

    void paintEvent(QPaintEvent *);

public slots:
    void onPostionChange(int x, int y);
    void onSizeChange(int w, int h);

private:
    QPixmap* backgroundPixmap_;
    QString info_;
    QRect rect_;
};

#endif // OERECT_H
