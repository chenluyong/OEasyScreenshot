# OEScreenshot的说明文档

为了方便各位使用，我利用 src/OEScreenshotLib.pro 生成了具备C接口的动态库 OEScreenshot.dll

大家可以动态的加载这个库，以达到快速使用截图功能的目的。


接口原型如下：

extern "C" void OEScreenshot(void);

我也提供了调用的示例程序

这个示例程序可以在 demo/ScreenShotLib 文件夹下轻松找到，希望它对你能产生帮助。



# 注意

 有些朋友可能会遇到加载动态库失败的问题，这里我需要简单的说一下课外知识

 在window下，若加载一个动态，那么必须能够在当前目录下或系统目录下搜索到，这个被加载的动态库所依赖的相关库，否则会加载失败。
