#ifndef OESCREENSHOT_H
#define OESCREENSHOT_H

#include <QWidget>

class OEScreen;
class OERect;
class OEAmplifier;

/*
* 截屏功能的主要入口
* 管理全局热键
* 资源的回收与释放
* 调用示例：
    OEScreenshot::Instance();
*/
class OEScreenshot : public QWidget
{
    Q_OBJECT

signals:

    void cursorPosChange(int, int);

    void doubleClick(void);

public:
    explicit OEScreenshot(QWidget *parent = 0);
    ~OEScreenshot(void);

    /*
     * 功能：窗口实例
     * 函数：Instance
     * 返回：OEScreenshot
     * 作者：陈鲁勇
     * 时间：2017年04月15日
     */
    static OEScreenshot *Instance();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *);

    /*
     * 功能：获得当前屏幕的大小
     * 函数：getScreenRect
     * 返回：QRect
     * 作者：陈鲁勇
     * 时间：2017年04月15日
     */
    const QRect& getScreenRect(void);

    /*
     * 获得屏幕的原画
     * 函数：getGlobalScreen
     * 返回：QPixmap* 指针
     * 作者：陈鲁勇
     * 时间：2017年04月15日
     */
    const QPixmap* getGlobalScreen(void);

private:

    /*
     * 初始化放大镜 (色彩采集器)
     * 函数：initAmplifier
     * 作者：陈鲁勇
     * 时间：2017年04月15日
     */
    void initAmplifier(void);

    /*
     * 测量控件 (大小感知器)
     * 函数：initMeasureWidget
     * 作者：陈鲁勇
     * 时间：2017年04月27日
     */
    void initMeasureWidget(void);

    /*
     * 初始化截屏背景
     * 函数：initGlobalScreen
     * 返回：QPixmap 经过暗色处理的屏幕图
     * 作者：陈鲁勇
     * 时间：2017年04月15日
     */
    const QPixmap* initGlobalScreen(void);

    /*
     * 初始化鼠标
     * 函数：initCursor
     * 参数：_ico 鼠标图片的资源文件
     * 作者：陈鲁勇
     * 时间：2017年04月15日
     */
    void initCursor(const QString& _ico);

    /*
     * 获得截图器
     * 函数：getScreen
     * 参数：pos 截图器的窗口起始位置
     * 返回：截图器实例
     * 作者：陈鲁勇
     * 时间：2017年04月16日
     */
    OEScreen* getScreen(const QPoint &pos);
    /*
     * 摧毁截图器
     * 函数：delScreen
     * 作者：陈鲁勇
     * 时间：2017年04月16日
     */
    void delScreen(void);

private:

    // 截屏窗口是否已经展示
    bool isScreenShow_;
    // 用于检测误操作
    QPoint startPoint_;
    // 当前桌面屏幕的矩形数据
    QRect desktopRect_;
    // 屏幕暗色背景图
    QPixmap *backgroundScreen_;
    // 屏幕原画
    QPixmap *originPainting_;
    // 截图屏幕
    OEScreen* screenTool_;
    OERect* rectTool_;
    // 截屏实例对象
    static OEScreenshot *self_;
};


#endif // OESCREENSHOT_H
