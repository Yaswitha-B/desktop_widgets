#include "MainWidget.h"
#include <QGuiApplication>
#include <QPainter>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnBottomHint | Qt::BypassWindowManagerHint);
    

    setAttribute(Qt::WA_TranslucentBackground);

    setAttribute(Qt::WA_TransparentForMouseEvents, false);

    // Set the widget to cover all screens
    QRect fullGeometry;
    const auto screens = QGuiApplication::screens();
    for (QScreen* screen : screens) {
        fullGeometry = fullGeometry.united(screen->geometry());
    }
    setGeometry(fullGeometry);
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor(0, 0, 0, 120); 
    painter.fillRect(rect(), bgColor);
}
MainWidget::~MainWidget() {}
