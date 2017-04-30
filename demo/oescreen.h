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



#ifndef OESCREEN_H
#define OESCREEN_H

#include <memory>
#include <QWidget>

class QMenu;

/**
 * @class : OEScreen
 * @brief : 截图器
 * @note  : 主要关乎图片的编辑与保存
*/
class OEScreen : public QWidget{

    Q_OBJECT

signals:


    /**
     * @brief : 截图器大小修改（信号）
     * @param : int 宽度
     * @param : int 高度
     * @date  : 2017年04月17日
     */
    void sizeChange(int,int);

    /**
     * @brief : 截图器窗口的位置（信号）
     * @param : int 窗口的横向位置
     * @param : int 窗口的纵向位置
     * @date  : 2017年04月17日
     */
    void postionChange(int,int);

    /**
     * @brief : 双击 （信号）
     * @date  : 2017年04月17日
     */
    void doubleClick(void);

protected:

    /// 内边距，决定拖拽的触发。
    const int PADDING_ = 6;

    /// 方位枚举
    enum DIRECTION {
        UPPER=0,
        LOWER=1,
        LEFT,
        RIGHT,
        LEFTUPPER,
        LEFTLOWER,
        RIGHTLOWER,
        RIGHTUPPER,
        NONE
    };

public:

    explicit OEScreen(std::shared_ptr<QPixmap> originPainting, QPoint pos, QWidget *parent = 0);

    ~OEScreen() { isInit_ = false; }

    /**
     * @brief : 获得当前截图器是否存在
     * @return: true : 存在
     * @date  : 2017年04月17日
     */
    static bool state(void) { return isInit_; }

protected:

    /**
     * @brief : 获得当前坐标点的边界方位
     * @param : cursor 当前鼠标的位置
     * @return: DIRECTION 鼠标的方位枚举
     * @date  : 2017年04月17日
     */
    DIRECTION getRegion(const QPoint &cursor);


    /**
     * @brief : 呼出菜单事件
     */
    virtual void contextMenuEvent(QContextMenuEvent *);

    /**
     * @brief : 双击事件
     */
    virtual void mouseDoubleClickEvent(QMouseEvent *e);

    /**
     * @brief : 鼠标按下事件
     */
    virtual void mousePressEvent(QMouseEvent *e);

    /**
     * @brief : 鼠标释放事件
     */
    virtual void mouseReleaseEvent(QMouseEvent *e);
    /**
     * @brief : 鼠标移动事件
     */
    virtual void mouseMoveEvent(QMouseEvent *e);

    /**
     * @brief : 窗口移动事件
     */
    virtual void moveEvent(QMoveEvent *);

    /**
     * @brief : 窗口大小修改事件
     */
    virtual void resizeEvent(QResizeEvent *);


    /**
     * @brief : 窗口显示事件
     */
    virtual void showEvent(QShowEvent *);

    /**
     * @brief : 窗口隐藏事件
     */
    virtual void hideEvent(QHideEvent *);

    /**
     * @brief : 鼠标进入窗口事件
     */
    virtual void enterEvent(QEvent *e);

    /**
     * @brief : 鼠标离开窗口事件
     */
    virtual void leaveEvent(QEvent *e);

    /**
     * @brief : 窗口关闭事件
     */
    virtual void closeEvent(QCloseEvent *);

    /**
     * @brief : 界面自绘事件
     */
    virtual void paintEvent(QPaintEvent *);

private:

    /**
     * @brief : 获得一个以时间格式命名的文件名
     * @return: QString 文件名
     * @date  : 2017年04月16日
     */
    virtual const QString getFileName(void);

public slots:


    /**
     * @brief : 根据鼠标位置修改窗口大小
     * @param : x 鼠标的横向位置
     * @param : y 鼠标的纵向位置
     * @date  : 2017年04月16日
     */
    void onMouseChange(int x,int y);

    /**
     * @brief : 保存屏幕到剪切板中
     * @date  : 2017年04月16日
     */
    void onSaveScreen(void);

protected slots:

    /**
     * @brief : 保存编辑屏幕到其他路径下
     * @note  : 会呼出路径选择的窗口
     * @date  : 2017年04月16日
     */
    void onSaveScreenOther(void);

    /**
     * @brief : 退出当前截图窗口
     * @date  : 2017年04月16日
     */
    void quitScreenshot(void);

private:

    /// 是否已经设置初始大小
    static bool isInit_;
    /// 窗口大小改变时，记录改变方向
    DIRECTION direction_;
    /// 起点
    QPoint originPoint_;
    /// 鼠标是否按下
    bool isPressed_;
    /// 拖动的距离
    QPoint movePos_;
    /// 标记锚点
    QPolygon listMarker_;
    /// 屏幕原画
    std::shared_ptr<QPixmap> originPainting_;
    /// 当前窗口几何数据 用于绘制截图区域
    QRect currentRect_;
    /// 右键菜单对象
    QMenu *menu_;

};

#endif /// OESCREEN_H
