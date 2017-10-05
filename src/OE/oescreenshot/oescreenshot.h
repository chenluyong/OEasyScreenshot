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


#ifndef OESCREENSHOT_H
#define OESCREENSHOT_H

#include <memory>
#include <QRect>
#include <QWidget>

class OEScreen;
class OERect;
class OEAmplifier;
class QTimer;
class QMenu;


/**
 * @class : OEScreenshot
 * @brief : 截屏功能的主要入口,
 *          管理全局热键,资源的回收与释放.
 * @remark: 调用示例( OEScreenshot::Instance(); )
*/
class OEScreenshot : public QWidget {
    Q_OBJECT

signals:

    /**
     * @brief : 鼠标移动（信号）
     * @param : int x轴的坐标
     * @param : int y轴的坐标
     * @date  : 2017年04月18日
     */
    void cursorPosChange(int, int);

    /**
     * @brief : 双击（信号）
     * @date  : 2017年04月18日
     */
    void doubleClick(void);

    /**
     * @brief : 鼠标当前位置最小的子窗口（信号）
     * @param : QRect 当前窗口的矩形数据
     * @date  : 2017年04月18日
     */
    void findChildWind(QRect);

public:
    /**
     * @brief : 构造函数
     * @note  : 当前依附的父窗口（一般不给父窗口）
     * @date  : 2017年04月16日
     */
    explicit OEScreenshot(QWidget *parent = 0);
    ~OEScreenshot(void);

    /**
     * @brief : 窗口实例
     * @note  : 通过这个函数获得截图器的整个实例
     * @return: 返回 OEScreenshot 实例指针
     * @date  : 2017年04月15日
     */
    static OEScreenshot *Instance(void);

    /**
     * @brief : 摧毁截图窗口
     * @note  : 通过这个函数可以摧毁整个截图窗口
     * @date  : 2017年04月30日
     */
    static void destroy(void);

protected:

    /**
     * @brief : 隐藏窗口事件
     */
    virtual void hideEvent(QHideEvent *);
    /**
     * @brief : 关闭窗口事件
     */
    virtual void closeEvent(QCloseEvent *);
    /**
     * @brief : 双击事件
     */
    virtual void mouseDoubleClickEvent(QMouseEvent*);
    /**
     * @brief : 鼠标按下事件
     */
    virtual void mousePressEvent(QMouseEvent *);
    /**
     * @brief : 鼠标释放事件
     */
    virtual void mouseReleaseEvent(QMouseEvent *e);
    /**
     * @brief : 鼠标移动事件
     */
    virtual void mouseMoveEvent(QMouseEvent *e);

    /**
     * @brief : 按键按下事件
     */
    virtual void keyPressEvent(QKeyEvent *e);
    /**
     * @brief : 自绘事件
     */
    virtual void paintEvent(QPaintEvent *);

    /**
     * @brief : 更新当前鼠标选区的窗口
     */
    void updateMouse(void);

private:


    /**
     * @brief : 初始化放大镜 (色彩采集器)
     * @note  : 他需要屏幕的原画作为放大器的放大元素
     * @param : originPainting 放大器必要的元素，若为空，则默认用originPainting_原画
     * @date  : 2017年04月15日
     * @remark: 需先行调用getGlobalScreen。
     */
    void initAmplifier(std::shared_ptr<QPixmap> originPainting = nullptr);

    /**
     * @brief : 测量控件 (大小感知器)
     * @date  : 2017年04月27日
     */
    void initMeasureWidget(void);

    /**
     * @brief : 初始化截屏背景
     * @return: QPixmap 经过暗色处理的屏幕图
     * @date  : 2017年04月15日
     */
    std::shared_ptr<QPixmap> initGlobalScreen(void);


    /**
     * @brief : 初始化鼠标
     * @note  : 为鼠标设置默认状态下的图标样式
     * @param : ico 鼠标图片的资源文件路径
     * @date  : 2017年04月15日
     * @remark: 若参数未填写，在使用本程序默认的鼠标Logo
     */
    void initCursor(const QString& ico = "");

    /**
     * @brief : 创建截图器
     * @note  : 若截图器已存在，则返回截图器示例，不会重复创建。
     * @param : pos 截图器的起始位置 （给当前鼠标位置即可）
     * @date  : 2017年04月16日
     * @remark: 创建截图器前，需要创建相关的组件，(例：大小感知器，放大取色器)
     */
    std::shared_ptr<OEScreen> createScreen(const QPoint &pos);

    /**
     * @brief : 摧毁截图器
     * @note  : 若截图器已存在，则摧毁示例，并清理示例创建的连带资源
     * @date  : 2017年04月16日
     */
    void destroyScreen(void);


    /**
     * @brief : 获得当前屏幕的大小
     * @note  : 这个函数是支持多屏幕的，示例：双屏幕 QRect（-1920, 0, 3840, 1080）
     * @return: 返回 QRect 引用
     * @date  : 2017年04月15日
     */
    const QRect& getScreenRect(void);

    /**
     * @brief : 获得屏幕的原画
     * @note  : 他不会重复获得屏幕原画，如果有，则返回原有的原画
     * @return: QPixmap* 指针
     * @date  : 2017年04月15日
     * @remark: 若想重新获得屏幕原画，需要清理原有资源
     */
    std::shared_ptr<QPixmap> getGlobalScreen(void);


private:

    /// 截屏窗口是否已经展示
    bool                        isLeftPressed_;
    /// 用于检测误操作
    QPoint                      startPoint_;
    /// 当前桌面屏幕的矩形数据
    QRect desktopRect_;
    /// 屏幕暗色背景图
    std::shared_ptr<QPixmap>    backgroundScreen_;
    /// 屏幕原画
    std::shared_ptr<QPixmap>    originPainting_;
    /// 截图屏幕
    std::shared_ptr<OEScreen>   screenTool_;
    /// 截图器大小感知器
    std::shared_ptr<OERect>     rectTool_;
    /// 放大取色器
    std::shared_ptr<OEAmplifier> amplifierTool_;
    /// 当前鼠标选区最小的矩形窗口
    QRect                       windowRect_;
    /// 截屏实例对象
    static OEScreenshot         *self_;
    /// 置顶定时器
    QTimer                      *egoisticTimer_;
    /// 活动窗口
    static bool                 isActivity_;
private slots:

    /**
     * @brief : Window下霸道置顶（唯我独尊）
     * @date  : 2017年04月28日
     * @remark: 使用该函数时，会终止右键菜单的行为，慎重使用，避免BUG
     */
    void onEgoistic(void);
};




/**
 * @class : OERect
 * @brief : 大小感知器
 * @note  : 主要关乎截图器左上方的大小感知控件
*/
class OERect : public QWidget {
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
    std::shared_ptr<QPixmap>    backgroundPixmap_;
    /// 显示的文字信息
    QString                     info_;
};


/**
 * @class : OEScreen
 * @brief : 截图器
 * @note  : 主要关乎图片的编辑与保存
*/
class OEScreen : public QWidget {

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
    static bool     isInit_;
    /// 窗口大小改变时，记录改变方向
    DIRECTION       direction_;
    /// 起点
    QPoint          originPoint_;
    /// 鼠标是否按下
    bool            isPressed_;
    /// 拖动的距离
    QPoint          movePos_;
    /// 标记锚点
    QPolygon        listMarker_;
    /// 屏幕原画
    std::shared_ptr<QPixmap> originPainting_;
    /// 当前窗口几何数据 用于绘制截图区域
    QRect           currentRect_;
    /// 右键菜单对象
    QMenu           *menu_;

};



#endif /// OESCREENSHOT_H
