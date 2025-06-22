#pragma once

#include <QWidget>
#include <QColor>

class StatArcWidget : public QWidget {
    Q_OBJECT
public:
    StatArcWidget(const QString &label, const QColor &color, QWidget *parent = nullptr);
    void setUsage(float percent);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString label;
    QColor color;
    float usage = 0.0f;
};
