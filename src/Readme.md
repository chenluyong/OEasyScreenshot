- 注：当前源码MinGW为实时更新的版本，MSVC同步性不高，建议使用MinGW，或妥善修改MSVC。
﻿- 详情查看 doc/build 目录下的文档


该文件夹包含了OEScreenshot核心文件。

通过加载  OEScreenshot  即可直接使用。

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


当前库秉承简单、独立的设计原则。


调用 Instance() 直接启动截图工具。

(单例模式：若截图工具已经启动，不会重复启动)

