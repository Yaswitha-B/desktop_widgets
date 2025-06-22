#include "DigitalClockWidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QRegion>
#include <QDebug>

DigitalClockWidget::DigitalClockWidget(QWidget *parent)
    : BaseWidget(parent), timer(new QTimer(this)) {

    resize(300, 300);
    setMinimumSize(150, 150);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Set circular mask
    setMask(QRegion(0, 0, width(), height(), QRegion::Ellipse));

    connect(timer, &QTimer::timeout, this, &DigitalClockWidget::updateTime);
    timer->start(1000);
    updateTime();
}

void DigitalClockWidget::resizeEvent(QResizeEvent *event) {
    setMask(QRegion(0, 0, width(), height(), QRegion::Ellipse));
    QWidget::resizeEvent(event);
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
    int margin = width() / 30;
    QRectF arcRect(margin, margin, width() - 2 * margin, height() - 2 * margin);
    QPen arcPen(Qt::white, std::max(2, width() / 100));
    painter.setPen(arcPen);
    painter.drawArc(arcRect, 90 * 16, -angle);

    // Time display
    int timeFontSize = std::max(10, width() / 7);
    QFont timeFont("Segoe UI", timeFontSize, QFont::Bold);
    painter.setFont(timeFont);
    painter.setPen(Qt::white);

    QString hour = currentTime.toString("hh");
    QString minute = currentTime.toString("mm");

    int textW = width() / 3;
    int textH = height() / 5;
    int textY = height() / 2 - textH / 2;
    QRect leftRect(width() / 6, textY, textW, textH);
    QRect rightRect(width() / 2, textY, textW, textH);
    painter.drawText(leftRect, Qt::AlignCenter, hour);
    painter.drawText(rightRect, Qt::AlignCenter, minute);

    // Vertical separator
    painter.setPen(QPen(Qt::white, std::max(1, width() / 150)));
    int sepY1 = textY + textH / 6;
    int sepY2 = textY + textH - textH / 6;
    painter.drawLine(width() / 2, sepY1, width() / 2, sepY2);

    // Date (day + weekday)
    int dateFontSize = std::max(8, width() / 18);
    QFont dateFont("Segoe UI", dateFontSize);
    painter.setFont(dateFont);
    painter.setPen(QColor("#cccccc"));

    QString dateText = currentDate.toString("dd");
    QString dayText = currentDate.toString("ddd").toUpper();

    int dateW = width() / 3;
    int dateH = height() / 10;
    int dateY = textY + textH + height() / 20;
    QRect dateRect(width() / 6, dateY, dateW, dateH);
    QRect dayRect(width() / 2, dateY, dateW, dateH);
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

void DigitalClockWidget::wheelEvent(QWheelEvent *event) {
    int delta = event->angleDelta().y();
    int step = (delta > 0) ? 20 : -20;
    int newSize = std::max(150, std::min(width() + step, 800));
    resize(newSize, newSize);
    event->accept();
}
