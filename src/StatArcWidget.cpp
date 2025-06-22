#include "StatArcWidget.h"
#include <QPainter>
#include <QFont>

StatArcWidget::StatArcWidget(const QString &label, const QColor &color, QWidget *parent)
    : QWidget(parent), label(label), color(color) {
    setFixedSize(110, 110);
}

void StatArcWidget::setUsage(float percent) {
    usage = percent;
    update();
}

void StatArcWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRectF rect(10, 10, width() - 20, height() - 20);

    p.setBrush(QColor(0, 0, 0, 180));
    p.setPen(Qt::NoPen);
    p.drawEllipse(rect);

    QPen arcPen(color, 6);
    p.setPen(arcPen);
    int span = static_cast<int>(usage * 360.0 / 100.0 * 16);
    p.drawArc(rect, 90 * 16, -span);

    p.setPen(Qt::white);
    QFont labelFont("Segoe UI", 9);
    p.setFont(labelFont);
    p.drawText(this->rect(), Qt::AlignTop | Qt::AlignHCenter, label);

    QFont valueFont("Segoe UI", 16, QFont::Bold);
    p.setFont(valueFont);
    p.drawText(this->rect(), Qt::AlignCenter, QString("%1%").arg((int)usage));
}
