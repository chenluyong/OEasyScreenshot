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


#ifndef COMMONHELPER_H
#define COMMONHELPER_H
#include <QString>
#include <QRect>

class QWidget;
class OECommonHelper
{
public:
    /**
    * setStyle
    * 功能：设置QSS文件
    * 参数：style 文件名
    * 作者：陈鲁勇
    * 日期：2017年04月10日
    **/
    static void setStyle(const QString &style);
    /**
    * setLanguagePack
    * 功能：设置语言包
    * 参数：language 语言包的文件名
    * 作者：陈鲁勇
    * 日期：2017年04月10日
    **/
    static void setLanguagePack(const QString& language);
    /**
    * moveCenter
    * 功能：将窗口移动到中心
    * 参数：widget 要移动的窗口
    * 参数：parentRect 矩形几何数据
    * 作者：陈鲁勇
    * 日期：2017年04月10日
    **/
    static void moveCenter(QWidget* widget, QRect parentRect = {});

    /**
    * getWindowWidthMultiplyingPower
    * 功能：获得当前界面与开发时的界面之间的横向倍率
    * 返回：float 倍率
    * 作者：陈鲁勇
    * 日期：2017年04月10日
    **/
    static const float& getWindowWidthMultiplyingPower(void);
    /**
    * 函数名：getWindowHeightMultiplyingPower
    * 功能：获得当前界面与开发时的界面之间的纵向倍率
    * 返回：float 倍率
    * 作者：陈鲁勇
    * 日期：2017年04月10日
    **/
    static const float& getWindowHeightMultiplyingPower(void);

    /**
    * 函数名：getSmallestWindowFromCursor
    * 功能：获得当前鼠标位置最小的子窗口
    * 参数：out_rect 矩形
    * 返回：成功:true
    * 作者：陈鲁勇
    * 日期：2017年04月10日
    **/
    static bool getSmallestWindowFromCursor(QRect &out_rect);

    /**
    * 函数名：getSmallestWindowFromCursor
    * 功能：获得当前鼠标位置的窗口
    * 参数：out_rect 矩形
    * 返回：成功:true
    * 作者：陈鲁勇
    * 日期：2017年04月10日
    **/
    static bool getCurrentWindowFromCursor(QRect &out_rect);

protected:

    /**
    * 函数名：upWindowSizeMultiplyingPower
    * 功能：更新窗口倍率
    * 作者：陈鲁勇
    * 日期：2017年04月10日
    **/
    static void upWindowSizeMultiplyingPower(void);


private:
    static float widthMultiplyingPower_;
    static float heightMultiplyingPower_;
};

#endif // COMMONHELPER_H
