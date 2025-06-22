#include "DigitalClockWidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QRegion>
#include <QDebug>

DigitalClockWidget::DigitalClockWidget(QWidget *parent)
    : BaseWidget(parent), timer(new QTimer(this)) {

    setFixedSize(300, 300);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Set circular mask
    setMask(QRegion(0, 0, width(), height(), QRegion::Ellipse));

    connect(timer, &QTimer::timeout, this, &DigitalClockWidget::updateTime);
    timer->start(1000);
    updateTime();
}

void DigitalClockWidget::updateTime() {
    currentTime = QTime::currentTime();
    currentDate = QDate::currentDate();
    update();
}

void DigitalClockWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background
    painter.setBrush(QColor(0, 0, 0, 180));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rect());

    // Seconds arc
    int angle = (currentTime.second() * 360 / 60) * 16;
    QRectF arcRect(10, 10, width() - 20, height() - 20);
    QPen arcPen(Qt::white, 3);
    painter.setPen(arcPen);
    painter.drawArc(arcRect, 90 * 16, -angle);

    // Time display
    QFont timeFont("Segoe UI", 42, QFont::Bold);
    painter.setFont(timeFont);
    painter.setPen(Qt::white);

    QString hour = currentTime.toString("hh");
    QString minute = currentTime.toString("mm");

    QRect leftRect(50, 80, 100, 60);
    QRect rightRect(150, 80, 100, 60);
    painter.drawText(leftRect, Qt::AlignCenter, hour);
    painter.drawText(rightRect, Qt::AlignCenter, minute);

    // Vertical separator
    painter.setPen(QPen(Qt::white, 2));
    painter.drawLine(width() / 2, 85, width() / 2, 130);

    // Date (day + weekday)
    QFont dateFont("Segoe UI", 14);
    painter.setFont(dateFont);
    painter.setPen(QColor("#cccccc"));

    QString dateText = currentDate.toString("dd");
    QString dayText = currentDate.toString("ddd").toUpper();

    QRect dateRect(50, 160, 100, 30);
    QRect dayRect(150, 160, 100, 30);
    painter.drawText(dateRect, Qt::AlignCenter, dateText);
    painter.drawText(dayRect, Qt::AlignCenter, dayText);
}

void DigitalClockWidget::mousePressEvent(QMouseEvent *event) {
    if (draggable && event->button() == Qt::LeftButton) {
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void DigitalClockWidget::mouseMoveEvent(QMouseEvent *event) {
    if (draggable && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - dragPosition);
    }
}

void DigitalClockWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        draggable = !draggable;
        setCursor(draggable ? Qt::OpenHandCursor : Qt::ArrowCursor);
        qDebug() << "Drag mode:" << (draggable ? "Enabled" : "Disabled");
    }
}
