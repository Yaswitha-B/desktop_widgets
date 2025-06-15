#pragma once

#include <QFrame>
#include <QMouseEvent>
#include <QTimer>

class BaseWidget : public QFrame
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);
    
    // Customization methods
    void setBorderWidth(int width);
    int getBorderWidth() const { return borderWidth; }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void onDoubleClickTimeout();

private:
    bool dragging;
    bool awaitingSecondClick;
    QPoint dragStartPosition;
    int borderWidth;
    QTimer *doubleClickTimer;
    
    // Helper methods (DRY principle)
    void initiateDrag(QMouseEvent *event);
    void performDrag(QMouseEvent *event);
    void finalizeDrag();
    void updateBorderStyle();
    void adjustSizeToChild();
};