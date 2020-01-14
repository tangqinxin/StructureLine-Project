#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H
#include <QImage>
#include <QWidget>
#include <QPainter>

// 自定义控件类
class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    QImage ImgToDraw;
    void ReSizeImg(QImage InputImg);//将输入的Qimage调整为和窗口大小一致
    void SetSize();
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    QSize DrawWigetSize;
};

#endif // DRAWWIDGET_H
