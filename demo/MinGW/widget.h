#ifndef WIDGET_H
#define WIDGET_H

#include <memory>
#include <QWidget>


namespace Ui {
class Widget;
}

class QPushButton;
class QxtGlobalShortcut;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void onScreenshot();
private:
    Ui::Widget *ui;

    std::shared_ptr<QPushButton> openScreenshotButton_;
    std::shared_ptr<QPushButton> closeScreenshotButton_;
};

#endif // WIDGET_H
