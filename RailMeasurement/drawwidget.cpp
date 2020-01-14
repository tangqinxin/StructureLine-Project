#include "drawwidget.h"
// 自定义控件，调用QPainter来实时画出检测的图像
DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{

}

void DrawWidget::ReSizeImg(QImage InputImg)
{
    ImgToDraw=InputImg.scaled(DrawWigetSize,Qt::IgnoreAspectRatio);
}

void DrawWidget::SetSize()
{
    DrawWigetSize=this->size();
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(0,0,ImgToDraw);
}
