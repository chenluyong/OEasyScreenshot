# 注意事项

## 编译发现编码，出现N+1条报错警告信息

    `根据自己的编译器去选择 pro 工程文件`
    `MSVC采用的是GBK2312的编码格式，MinGW采用的是UTF-8的编码格式`

    很多朋友说为什么打开以后编码不同，爆了很多错误。

    首先对此问题，先做声明，我们使用的是Qt Creator 4 以上的 IDE，并使用UTF-8作为编码格式。
    若与以上信息有出入，需要对文件进行修改。如果修改完毕，为帮助其他朋友，烦请将您修改后的代码 Pull 到开源社区，
    或者发送 e-mail 到 727057301@qq.com，感谢您的付出。


    如果你使用的是 Qt Creator 且你出现编码不同而导致的编译失败，可以查看下当前构建环境是否使用了 MSVC 的编译器。
    该编译器属于 VC++ 编译器，可能在字符集上与MinGW有出入，使用并建议使用 MinGW 编译器，可以改善这个问题。


### MinGW 介绍

    MinGW，是Minimalist GNUfor Windows的缩写。它是一个可自由使用和自由发布的Windows特定
    头文件和使用GNU工具集导入库的集合，允许你在GNU/Linux和Windows平台生成本地的Windows程序
    而不需要第三方C运行时（C Runtime）库。

### MSVC 介绍

    他是微软的一款编译器，支持且仅支持 Windows 操作系统。
    此软件包安装 C 运行时 (CRT)、标准 C++、ATL、MFC、OpenMP 和 MSDIA 库的运行时组件。
    对于支持并行部署模型的库（CRT、SCL、ATL、MFC、OpenMP），这些运行时组件被安装到支持
    并行程序集的 Windows 操作系统的本机程序集