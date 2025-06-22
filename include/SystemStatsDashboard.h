#pragma once

#include "BaseWidget.h"
#include <QTimer>
#include <QMouseEvent>

class StatArcWidget;

class SystemStatsDashboard : public BaseWidget {
    Q_OBJECT
public:
    explicit SystemStatsDashboard(QWidget *parent = nullptr);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void updateStats();

private:
    QTimer *timer;
    StatArcWidget *cpu, *memory, *disk;

    float getCpu();
    float getMem();
    float getDisk();

    // CPU history
    quint64 lastIdle = 0, lastTotal = 0;

    // Dragging state
    bool draggable = false;
    QPoint dragStartPos;
};
