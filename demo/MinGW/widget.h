#ifndef WIDGET_H
#define WIDGET_H

#include <memory>
#include <QWidget>

class QPushButton;
class QxtGlobalShortcut;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

protected slots:

    void onScreenshot();

private:

    std::shared_ptr<QPushButton> openScreenshotButton_;
    std::shared_ptr<QPushButton> closeScreenshotButton_;

};

#endif // WIDGET_H
