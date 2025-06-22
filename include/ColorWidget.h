#pragma once
#include "BaseWidget.h"
#include <QColor>

class ColorWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QColor currentColor;
    void toggleColor();
};

