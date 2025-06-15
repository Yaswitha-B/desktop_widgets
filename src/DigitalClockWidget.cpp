#include "DigitalClockWidget.h"
#include <QPainter>

DigitalClockWidget::DigitalClockWidget(QWidget *parent)
    : BaseWidget(parent), timer(new QTimer(this))
{
    connect(timer, &QTimer::timeout, this, &DigitalClockWidget::updateTime);
    timer->start(1000); // 1-second interval
    currentTime = QTime::currentTime();
}

void DigitalClockWidget::updateTime()
{
    currentTime = QTime::currentTime();
    update(); // Trigger a repaint
}

void DigitalClockWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background
    painter.fillRect(rect(), QColor("#1e1e1e")); // Dark background

    // Clock text
    painter.setPen(Qt::white);
    painter.setFont(QFont("Courier", 24, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, currentTime.toString("hh:mm:ss"));
}
