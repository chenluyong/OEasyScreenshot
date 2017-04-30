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


#ifndef OERECT_H
#define OERECT_H
#include <memory>
#include <QWidget>
#include <QRect>

/**
 * @class : OERect
 * @brief : 大小感知器
 * @note  : 主要关乎截图器左上方的大小感知控件
*/
class OERect : public QWidget
{
    Q_OBJECT

signals:


public:

    explicit OERect(QWidget *parent = 0);

protected:

    /**
     * @brief : 自绘函数
     */
    void paintEvent(QPaintEvent *);

public slots:

    /**
     * @brief : 外部组件位置修改（槽）
     * @note  : 感知器修改自身位置
     * @param : x 横向位置
     * @param : y 纵向位置
     * @date  : 2017年04月15日
     */
    void onPostionChange(int x, int y);

    /**
     * @brief : 外部组件大小修改 （槽）
     * @note  : 感知器修改显示的大小数据
     * @param : w 宽度
     * @param : h 高度
     * @date  : 2017年04月15日
     */
    void onSizeChange(int w, int h);

private:
    /// 背景色
    std::shared_ptr<QPixmap> backgroundPixmap_;
    /// 显示的文字信息
    QString info_;
};

#endif /// OERECT_H
