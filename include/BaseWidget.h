#pragma once
#include <QFrame>
#include <QMouseEvent>
#include <QPoint>

class BaseWidget : public QFrame {
    Q_OBJECT

public:
    explicit BaseWidget(QWidget *parent = nullptr);
    ~BaseWidget() override = default;

    void setBorderWidth(int width);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool isDragging = false;
    QPoint dragStartPosition;
    int borderWidth = 1;

    void updateBorderStyle();
    void adjustSizeToChild();
};
