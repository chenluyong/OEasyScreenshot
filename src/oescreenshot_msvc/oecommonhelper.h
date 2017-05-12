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



#ifndef COMMONHELPER_H
#define COMMONHELPER_H
#include <QString>
#include <QRect>

class QWidget;

/**
 * @class : OECommonHelper
 * @brief : 通用助手
 * @note  : 完成一些比较常用又通用的功能
 */
class OECommonHelper
{
public:

    /**
    * @brief : 设置QSS文件
    * @param : style 文件名
    * @author: 陈鲁勇
    * @date  : 2017年04月10日
    * @remark: 如果是qrc路径，请带上 qrc:/
    **/
    static void setStyle(const QString &style);

    /**
    * @brief : 设置语言包
    * @param : language 语言包的文件名
    * @author: 陈鲁勇
    * @date  : 2017年04月10日
    **/
    static void setLanguagePack(const QString& language);

    /**
    * @brief : 将窗口移动到中心
    * @param : widget 要移动的窗口
    * @param : parentRect 矩形几何数据
    * @author: 陈鲁勇
    * @date  : 2017年04月10日
    **/
    static void moveCenter(QWidget* widget, QRect parentRect = {});


    /**
    * @brief : 获得当前界面与开发时的界面之间的横向倍率
    * @return: float 倍率
    * @author: 陈鲁勇
    * @date  : 2017年04月10日
    **/
    static const float& getWindowWidthMultiplyingPower(void);


    /**
    * @brief : 获得当前界面与开发时的界面之间的纵向倍率
    * @return: float 倍率
    * @author: 陈鲁勇
    * @date  : 2017年04月10日
    **/
    static const float& getWindowHeightMultiplyingPower(void);


    /**
    * @brief : 获得当前鼠标位置最小的子窗口
    * @param : out_rect 矩形 (返回)
    * @return: 成功:true
    * @author: 陈鲁勇
    * @date  : 2017年04月10日
    **/
    static bool getSmallestWindowFromCursor(QRect &out_rect);

    /**
    * @brief : 获得当前鼠标位置的窗口
    * @param : out_rect 矩形 (返回)
    * @return: 成功:true
    * @author: 陈鲁勇
    * @date  : 2017年04月10日
    **/
    static bool getCurrentWindowFromCursor(QRect &out_rect);

protected:

    /**
    * @brief : 更新窗口倍率
    * @author: 陈鲁勇
    * @date  : 2017年04月10日
    **/
    static void upWindowSizeMultiplyingPower(void);


private:
    /// 窗口横向倍率
    static float widthMultiplyingPower_;
    /// 窗口纵向倍率
    static float heightMultiplyingPower_;
};

#endif /// COMMONHELPER_H
