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

    void done(void) { isInit_ = true; }
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

    virtual void enterEvent(QEvent *e);
    virtual void leaveEvent(QEvent *e);

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
     * 作者：陈鲁勇
     * 时间：2017年04月16日
     */
    void onMouseChange(int w,int h);

    /*
     * 功能：保存屏幕到剪切板中
     * 函数：onSaveScreenOther
     * 作者：陈鲁勇
     * 时间：2017年04月16日
     */
    void onSaveScreen(void);

protected slots:

    /*
     * 功能：保存编辑屏幕到其他路径下
     * 函数：onSaveScreenOther
     * 作者：陈鲁勇
     * 时间：2017年04月16日
     */
    void onSaveScreenOther(void);

    /*
     * 功能：退出当前截图窗口
     * 函数：quitApp
     * 作者：陈鲁勇
     * 时间：2017年04月16日
     */
    void quitScreenshot(void);

private:
    // 是否已经设置初始大小
    bool isInit_;
    // 窗口大小改变时，记录改变方向
    DIRECTION direction_;
    // 起点
    QPoint originPoint_;
    // 鼠标是否按下
    bool isPressed_;
    // 拖动的距离
    QPoint movePos_;
    // 屏幕原画
    QPixmap* originPainting_;
    // 当前窗口几何数据 用于绘制截图区域
    QRect currentRect_;
    //右键菜单对象
    QMenu *menu_;

};

#endif // OESCREEN_H
