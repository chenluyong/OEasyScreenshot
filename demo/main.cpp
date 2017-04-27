#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <oescreenshot.h>
#include <QScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 启用截屏
    OEScreenshot::Instance();
    return a.exec();
}
