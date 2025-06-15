#include "MainWidget.h" 

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TransparentForMouseEvents, true); 
    resize(800, 600); 
    move(100, 100); 
}

MainWidget::~MainWidget() = default;
