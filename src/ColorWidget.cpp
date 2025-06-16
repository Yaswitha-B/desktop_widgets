#include "ColorWidget.h"
#include <QPainter>
#include <QMouseEvent>

ColorWidget::ColorWidget(QWidget *parent)
    : BaseWidget(parent), currentColor(Qt::red)
{
    setFixedSize(100, 100); 
}

void ColorWidget::paintEvent(QPaintEvent *event) 
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(currentColor);
    painter.drawRect(contentsRect()); 
}

void ColorWidget::mousePressEvent(QMouseEvent *event)
{

    BaseWidget::mousePressEvent(event);
    
    if (!event->isAccepted() && event->button() == Qt::LeftButton && contentsRect().contains(event->pos())) {
        toggleColor();
        update();
        event->accept();
    }
}

void ColorWidget::toggleColor()
{
    currentColor = (currentColor == Qt::red) ? Qt::blue : Qt::red;
}
