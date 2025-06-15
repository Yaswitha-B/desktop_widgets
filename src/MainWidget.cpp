#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    move(100, 100);

}

MainWidget::~MainWidget() = default;
