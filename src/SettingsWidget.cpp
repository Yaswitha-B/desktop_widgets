#include "SettingsWidget.h"
#include <QPainter>
#include <QMouseEvent>

SettingsWidget::SettingsWidget(QWidget *parent)
    : BaseWidget(parent), managerDialog(nullptr)
{
    setFixedSize(60, 60);
    setAttribute(Qt::WA_TranslucentBackground);
}

void SettingsWidget::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF rect(1, 1, width() - 2, height() - 2);
    painter.setBrush(QColor(255, 255, 255, 230));
    painter.setPen(QPen(QColor("#2196f3"), 2));
    painter.drawEllipse(rect);

    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));

    int lineWidth = width() - 24;
    int x = (width() - lineWidth) / 2;
    int yStart = 18;
    int lineSpacing = 10;

    for (int i = 0; i < 3; ++i) {
        int y = yStart + i * lineSpacing;
        painter.drawLine(x, y, x + lineWidth, y);
    }
}

void SettingsWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        WidgetManagerDialog dialog(parentWidget());
        dialog.exec();
    }
    BaseWidget::mousePressEvent(event);
}