// colorwidget.cpp
#include "ColorWidget.h"
#include <QPainter>
#include <QMouseEvent>

ColorWidget::ColorWidget(QWidget *parent)
    : BaseWidget(parent), currentColor(Qt::red)
{
    setFixedSize(100, 100); // Set size
}

void ColorWidget::paintEvent(QPaintEvent *event) // Added event name
{
    QFrame::paintEvent(event); // Call QFrame's paintEvent to draw the frame

    QPainter painter(this);
    painter.setBrush(currentColor);
    painter.drawRect(contentsRect()); // Draw inside the frame
}

void ColorWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        toggleColor();
        update();
    }
}

void ColorWidget::toggleColor()
{
    currentColor = (currentColor == Qt::red) ? Qt::blue : Qt::red;
}
