#ifndef OERECT_H
#define OERECT_H

#include <QWidget>
#include <QRect>

class OERect : public QWidget
{
    Q_OBJECT

signals:


public:

    explicit OERect(QWidget *parent = 0);

protected:

    void paintEvent(QPaintEvent *);

public slots:
    void onPostionChange(int x, int y);
    void onSizeChange(int w, int h);

private:
    QPixmap* backgroundPixmap_;
    QString info_;
    QRect rect_;
};

#endif // OERECT_H
