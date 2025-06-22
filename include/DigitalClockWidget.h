#pragma once

#include "BaseWidget.h"
#include <QTimer>
#include <QTime>
#include <QDate>
#include <QMouseEvent>

class DigitalClockWidget : public BaseWidget {
    Q_OBJECT
public:
    explicit DigitalClockWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QTimer *timer;
    QTime currentTime;
    QDate currentDate;
    QPoint dragPosition;
    bool draggable = false;
    void updateTime();
};
