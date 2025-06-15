#pragma once

#include "BaseWidget.h"
#include <QTimer>
#include <QTime>

class DigitalClockWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit DigitalClockWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *timer;
    QTime currentTime;

    void updateTime();
};
