#include "SystemStatsDashboard.h"
#include "StatArcWidget.h"
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <sys/statvfs.h>
#include <QMouseEvent>

SystemStatsDashboard::SystemStatsDashboard(QWidget *parent)
    : BaseWidget(parent) {
    setFixedSize(360, 140);
    setStyleSheet("background-color: rgba(20, 20, 20, 180);");
    setToolTip("Double-click to drag");  // ✨ Cute little hint

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    cpu = new StatArcWidget("CPU", QColor("#00cfff"));
    memory = new StatArcWidget("Memory", QColor("#00bcd4"));
    disk = new StatArcWidget("Disk", QColor("#03a9f4"));

    layout->addWidget(cpu);
    layout->addWidget(memory);
    layout->addWidget(disk);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SystemStatsDashboard::updateStats);
    timer->start(1000);

    updateStats();
}

void SystemStatsDashboard::updateStats() {
    cpu->setUsage(getCpu());
    memory->setUsage(getMem());
    disk->setUsage(getDisk());
}

float SystemStatsDashboard::getCpu() {
    QFile file("/proc/stat");
    if (!file.open(QIODevice::ReadOnly)) return 0.0f;

    QByteArray line = file.readLine();
    QList<QByteArray> v = line.simplified().split(' ');

    quint64 user = v[1].toULongLong();
    quint64 nice = v[2].toULongLong();
    quint64 system = v[3].toULongLong();
    quint64 idle = v[4].toULongLong();
    quint64 total = user + nice + system + idle;

    quint64 totalDiff = total - lastTotal;
    quint64 idleDiff = idle - lastIdle;

    lastTotal = total;
    lastIdle = idle;

    return totalDiff == 0 ? 0 : (1.0f - (float)idleDiff / totalDiff) * 100.0f;
}

float SystemStatsDashboard::getMem() {
    QFile file("/proc/meminfo");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return 0.0f;

    QTextStream in(&file);
    quint64 total = 0, available = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(QChar(' '), Qt::SkipEmptyParts);
        if (parts.size() < 2) continue;

        if (parts[0] == "MemTotal:")
            total = parts[1].toULongLong();
        else if (parts[0] == "MemAvailable:")
            available = parts[1].toULongLong();
        if (total && available) break;
    }

    return total > 0 ? (1.0 - (float)available / total) * 100.0f : 0.0f;
}

float SystemStatsDashboard::getDisk() {
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) return 0.0f;

    quint64 total = stat.f_blocks * stat.f_frsize;
    quint64 free = stat.f_bavail * stat.f_frsize;
    return total > 0 ? (1.0 - (float)free / total) * 100.0f : 0.0f;
}

// ------- Dragging Support after Double Click ---------
void SystemStatsDashboard::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        draggable = !draggable;
    }
}

void SystemStatsDashboard::mousePressEvent(QMouseEvent *event) {
    if (draggable && event->button() == Qt::LeftButton) {
        dragStartPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void SystemStatsDashboard::mouseMoveEvent(QMouseEvent *event) {
    if (draggable && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - dragStartPos);
    }
}
