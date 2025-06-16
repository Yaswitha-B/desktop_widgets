#pragma once

#include <QFrame>
#include <QMouseEvent>

class BaseWidget : public QFrame
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);

    void setBorderWidth(int width);
    int getBorderWidth() const { return borderWidth; }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool dragging;
    QPoint dragStartPosition;
    int borderWidth;

    void updateBorderStyle();
    void adjustSizeToChild();
};