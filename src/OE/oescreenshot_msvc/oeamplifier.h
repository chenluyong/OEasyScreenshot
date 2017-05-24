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



#ifndef OEAMPLIFIER_H
#define OEAMPLIFIER_H
#include <memory>
#include <QWidget>


/**
 * @class : OEAmplifier
 * @brief : 放大取色器
 * @note  : 关于鼠标位置局部放大的操作以及色卡取值的操作
 */
class OEAmplifier : public QWidget
{
    Q_OBJECT
public:
    explicit OEAmplifier(std::shared_ptr<QPixmap> originPainting, QWidget *parent = 0);

signals:

public slots:


    /**
     * @brief : 大小修改
     * @param : w 宽度
     * @param : h 高度
     * @date  : 2017年4月29日
     */
    void onSizeChange(int w, int h);

    /**
     * @brief : 大小修改
     * @param : w 宽度
     * @param : h 高度
     * @date  : 2017年4月29日
     */
    void onPostionChange(int x, int y);

protected:

    /**
     * @brief : 窗口自绘事件
     * @date  : 2017年4月29日
     */
    virtual void paintEvent(QPaintEvent *);

private:

    /// 外部组件的大小信息
    QSize screenSize_;
    /// 鼠标的位置
    QPoint cursorPoint_;
    /// 取色放大器的边长
    int sideLength_;
    /// 放大区的高度
    int imageHeight_;
    /// 屏幕原画
    std::shared_ptr<QPixmap> originPainting_;

};

#endif /// OEAMPLIFIER_H
