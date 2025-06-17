#include "DigitalClockWidget.h"
#include <QPainter>

DigitalClockWidget::DigitalClockWidget(QWidget *parent)
    : BaseWidget(parent), timer(new QTimer(this))
{
    setFixedSize(200, 80); 
    connect(timer, &QTimer::timeout, this, &DigitalClockWidget::updateTime);
    timer->start(1000); 
    updateTime(); 
}

void DigitalClockWidget::updateTime()
{
    currentTime = QTime::currentTime();
    update(); 
}

void DigitalClockWidget::paintEvent(QPaintEvent *event)
{
    BaseWidget::paintEvent(event); 

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect innerRect = contentsRect();
    painter.fillRect(innerRect, QColor("#1e1e1e")); 

    painter.setPen(Qt::white);
    painter.setFont(QFont("Courier", 24, QFont::Bold));
    painter.drawText(innerRect, Qt::AlignCenter, currentTime.toString("hh:mm:ss"));
}
