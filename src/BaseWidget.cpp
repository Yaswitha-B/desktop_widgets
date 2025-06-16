#include "BaseWidget.h"
#include <QApplication>
#include <QLayout>

BaseWidget::BaseWidget(QWidget *parent)
    : QFrame(parent), dragging(false), borderWidth(4)
{
    setAttribute(Qt::WA_Hover, true);
    updateBorderStyle();
    setMouseTracking(true);
}

void BaseWidget::setBorderWidth(int width)
{
    borderWidth = qMax(3, width); 
    updateBorderStyle();
    adjustSizeToChild();
}

void BaseWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        
        QPoint localPos = event->pos();
        QRect frameRect = rect();
        QRect contentRect = contentsRect();
        
        bool inFrame = frameRect.contains(localPos) && !contentRect.contains(localPos);
        
        if (inFrame) {
            dragging = true;
            dragStartPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
    }
    QFrame::mousePressEvent(event);
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - dragStartPosition);
        event->accept();
        return;
    }
    QFrame::mouseMoveEvent(event);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragging) {
        dragging = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    QFrame::mouseReleaseEvent(event);
}



void BaseWidget::updateBorderStyle()
{
    setFrameStyle(QFrame::Box | QFrame::Plain);
    setLineWidth(borderWidth);
    
    QString style = QString("BaseWidget { border: %1px solid #90a4ae; border-radius: 3px; background-color: rgba(255, 255, 255, 50); } BaseWidget:hover { border-color: #2196f3; background-color: rgba(255, 255, 255, 100); }").arg(borderWidth);
    
    setStyleSheet(style);
}

void BaseWidget::adjustSizeToChild()
{
    if (layout()) {
        layout()->setSizeConstraint(QLayout::SetFixedSize);
        layout()->setContentsMargins(borderWidth, borderWidth, borderWidth, borderWidth);
        return;
    }
    
    QSize maxSize;
    for (QObject *child : children()) {
        if (auto *widget = qobject_cast<QWidget*>(child)) {
            maxSize = maxSize.expandedTo(widget->sizeHint());
        }
    }
    
    if (!maxSize.isEmpty()) {
        resize(maxSize + QSize(borderWidth * 2, borderWidth * 2));
    }
}