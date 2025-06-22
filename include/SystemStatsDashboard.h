#pragma once
#include "BaseWidget.h"
#include <QTimer>

class StatArcWidget; // Forward declaration

class SystemStatsDashboard : public BaseWidget {
    Q_OBJECT

public:
    explicit SystemStatsDashboard(QWidget *parent = nullptr);

private slots:
    void updateStats();

private:
    StatArcWidget *cpu;
    StatArcWidget *memory;
    StatArcWidget *disk;
    QTimer *timer;

    quint64 lastTotal;
    quint64 lastIdle;

    float getCpu();
    float getMem();
    float getDisk();
};

