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


#ifndef OESCREENSHOT_H
#define OESCREENSHOT_H

#include <QWidget>

class OEScreen;
class OERect;
class OEAmplifier;
class QTimer;

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

    void findChildWind(QRect);

public:
    explicit OEScreenshot(QWidget *parent = 0);
    ~OEScreenshot(void);

    /*
     * 功能：窗口实例
     * 函数：Instance
     * 返回：OEScreenshot
     * 时间：2017年04月15日
     */
    static OEScreenshot *Instance();

protected:

    virtual void mouseDoubleClickEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *e);

    /*
     * 功能：获得当前屏幕的大小
     * 函数：getScreenRect
     * 返回：QRect
     * 时间：2017年04月15日
     */
    const QRect& getScreenRect(void);

    /*
     * 获得屏幕的原画
     * 函数：getGlobalScreen
     * 返回：QPixmap* 指针
     * 时间：2017年04月15日
     */
    const QPixmap* getGlobalScreen(void);


private:

    /*
     * 初始化放大镜 (色彩采集器)
     * 函数：initAmplifier
     * 时间：2017年04月15日
     */
    void initAmplifier(void);

    /*
     * 测量控件 (大小感知器)
     * 函数：initMeasureWidget
     * 时间：2017年04月27日
     */
    void initMeasureWidget(void);

    /*
     * 初始化截屏背景
     * 函数：initGlobalScreen
     * 返回：QPixmap 经过暗色处理的屏幕图
     * 时间：2017年04月15日
     */
    const QPixmap* initGlobalScreen(void);

    /*
     * 初始化鼠标
     * 函数：initCursor
     * 参数：_ico 鼠标图片的资源文件
     * 时间：2017年04月15日
     */
    void initCursor(const QString& _ico);

    /*
     * 获得截图器
     * 函数：createScreen
     * 参数：pos 截图器的窗口起始位置
     * 返回：截图器实例
     * 时间：2017年04月16日
     */
    OEScreen* createScreen(const QPoint &pos);
    /*
     * 摧毁截图器
     * 函数：delScreen
     * 时间：2017年04月16日
     */
    void destroyScreen(void);

private:

    // 截屏窗口是否已经展示
    bool isLeftPressed_;
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
    // 截图器大小感知器
    OERect* rectTool_;
    // 放大取色器
    OEAmplifier* amplifierTool_;
    // 当前鼠标选区最小的矩形窗口
    QRect windowRect_;
    // 截屏实例对象
    static OEScreenshot *self_;
    // 置顶定时器
    QTimer* egoisticTimer_;
    bool isTop_;

private slots:

    /*
     * Window下霸道置顶（唯我独尊）
     * 函数：onEgoistic
     * 时间：2017年04月28日
     */
    void onEgoistic(void);
};


#endif // OESCREENSHOT_H
