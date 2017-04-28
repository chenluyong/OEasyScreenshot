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


#ifndef OESCREEN_H
#define OESCREEN_H

#include <QWidget>

class QMenu;

/*
 * 截图器
 * 图片编辑与保存
*/
class OEScreen : public QWidget{

    Q_OBJECT

signals:

    void sizeChange(int,int);

    void postionChange(int,int);

    void doubleClick(void);

protected:

    // 内边距，决定拖拽的触发。
    const int PADDING_ = 5;


    enum DIRECTION {
        UP=0,
        DOWN=1,
        LEFT,
        RIGHT,
        LEFTTOP,
        LEFTBOTTOM,
        RIGHTBOTTOM,
        RIGHTTOP,
        NONE
    };

public:

    explicit OEScreen(QPixmap* originPainting, QPoint pos, QWidget *parent = 0);

    ~OEScreen() { isInit_ = false; }
    static bool state(void) { return isInit_; }

    void setOriginPoint(const QPoint& pt) {originPoint_ = pt;}
protected:

    /*
     * 功能：获得当前坐标点的边界方位
     * 函数：region
     * 参数：cursor 鼠标位置
     * 返回：方位枚举，鼠标不在边界则返回 NONE
    */
    DIRECTION getRegion(const QPoint &cursor);


    virtual void contextMenuEvent(QContextMenuEvent *);

    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);

    virtual void moveEvent(QMoveEvent *);
    virtual void resizeEvent(QResizeEvent *);


    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);
    virtual void enterEvent(QEvent *e);
    virtual void leaveEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *);

    virtual void paintEvent(QPaintEvent *);

private:

    /*
     * 功能：获得一个以时间格式命名的文件名
     * 函数：getFileName
     * 返回：QString 文件名
     * 作者：陈鲁勇
     * 时间：2017年04月16日
     */
    virtual const QString getFileName(void);

public slots:

    /*
     * 功能：修改窗口大小 支持负值窗口的修改
     * 函数：onSizeChange
     * 参数：w 宽度
     * 参数：h 高度
     * 时间：2017年04月16日
     */
    void onMouseChange(int w,int h);

    /*
     * 功能：保存屏幕到剪切板中
     * 函数：onSaveScreenOther
     * 时间：2017年04月16日
     */
    void onSaveScreen(void);

protected slots:

    /*
     * 功能：保存编辑屏幕到其他路径下
     * 函数：onSaveScreenOther
     * 时间：2017年04月16日
     */
    void onSaveScreenOther(void);

    /*
     * 功能：退出当前截图窗口
     * 函数：quitScreenshot
     * 时间：2017年04月16日
     */
    void quitScreenshot(void);

private:

    // 是否已经设置初始大小
    static bool isInit_;
    // 窗口大小改变时，记录改变方向
    DIRECTION direction_;
    // 起点
    QPoint originPoint_;
    // 鼠标是否按下
    bool isPressed_;
    // 拖动的距离
    QPoint movePos_;
    // 标记锚点
    QPolygon listMarker_;
    // 屏幕原画
    QPixmap* originPainting_;
    // 当前窗口几何数据 用于绘制截图区域
    QRect currentRect_;
    //右键菜单对象
    QMenu *menu_;

};

#endif // OESCREEN_H
