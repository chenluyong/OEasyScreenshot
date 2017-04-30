#ifndef OESCREENSHOTWIDGET_H
#define OESCREENSHOTWIDGET_H

#include <memory>
#include <QWidget>


class QPushButton;
class QxtGlobalShortcut;
class OEScreenshotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OEScreenshotWidget(QWidget *parent = 0);

signals:

public slots:
    void onScreenshot(void);

private:
    std::shared_ptr<QPushButton> openScreenshotButton_;
    std::shared_ptr<QPushButton> closeScreenshotButton_;
};

#endif // OESCREENSHOTWIDGET_H
