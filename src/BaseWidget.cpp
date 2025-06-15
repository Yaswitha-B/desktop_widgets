#include "BaseWidget.h"
#include <QApplication>
#include <QLayout>
#include <QResizeEvent>

BaseWidget::BaseWidget(QWidget *parent)
    : QFrame(parent), dragging(false), awaitingSecondClick(false), borderWidth(6)
{
    // Initialize double-click timer
    doubleClickTimer = new QTimer(this);
    doubleClickTimer->setSingleShot(true);
    doubleClickTimer->setInterval(QApplication::doubleClickInterval());
    connect(doubleClickTimer, &QTimer::timeout, this, &BaseWidget::onDoubleClickTimeout);
    
    // Initial border setup
    updateBorderStyle();
    
    // Enable hover events for visual feedback
    setAttribute(Qt::WA_Hover, true);
}

void BaseWidget::setBorderWidth(int width)
{
    borderWidth = qMax(2, width); // Minimum 2px border
    updateBorderStyle();
    adjustSizeToChild();
}

void BaseWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (awaitingSecondClick) {
            // This is the second click - start dragging
            initiateDrag(event);
            doubleClickTimer->stop();
            awaitingSecondClick = false;
            return;
        } else if (!dragging) {
            // First click - start waiting for second click
            awaitingSecondClick = true;
            doubleClickTimer->start();
            event->accept();
            return;
        }
    }
    
    QFrame::mousePressEvent(event);
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        performDrag(event);
        return;
    }
    
    QFrame::mouseMoveEvent(event);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragging) {
        finalizeDrag();
        return;
    }
    
    QFrame::mouseReleaseEvent(event);
}

void BaseWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        initiateDrag(event);
        return;
    }
    
    QFrame::mouseDoubleClickEvent(event);
}

void BaseWidget::onDoubleClickTimeout()
{
    // Double-click window expired - reset state
    awaitingSecondClick = false;
}

void BaseWidget::initiateDrag(QMouseEvent *event)
{
    dragging = true;
    awaitingSecondClick = false;
    dragStartPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
    setCursor(Qt::ClosedHandCursor);
    
    // Visual feedback during drag
    setStyleSheet(
        QString("BaseWidget { "
                "border: %1px solid #2196f3; "
                "border-radius: 3px; "
                "background-color: rgba(33, 150, 243, 50); "
                "}").arg(borderWidth)
    );
    
    event->accept();
}

void BaseWidget::performDrag(QMouseEvent *event)
{
    const QPoint newPos = event->globalPosition().toPoint() - dragStartPosition;
    move(newPos);
    event->accept();
}

void BaseWidget::finalizeDrag()
{
    dragging = false;
    setCursor(Qt::ArrowCursor);
    updateBorderStyle(); // Restore normal appearance
}

void BaseWidget::updateBorderStyle()
{
    // Adaptive border styling
    setFrameStyle(QFrame::Box | QFrame::Plain);
    setLineWidth(borderWidth);
    
    setStyleSheet(
        QString("BaseWidget { "
                "border: %1px solid #90a4ae; "
                "border-radius: 3px; "
                "background-color: rgba(240, 248, 255, 200); "
                "} "
                "BaseWidget:hover { "
                "border-color: #5c6bc0; "
                "background-color: rgba(240, 248, 255, 230); "
                "}").arg(borderWidth)
    );
}

void BaseWidget::adjustSizeToChild()
{
    // Auto-adjust size based on child widgets
    if (layout()) {
        // If there's a layout, let it determine the size
        layout()->setSizeConstraint(QLayout::SetFixedSize);
        layout()->setContentsMargins(borderWidth, borderWidth, borderWidth, borderWidth);
    } else {
        // Find the largest child widget and adjust accordingly
        QSize maxChildSize;
        for (QObject *child : children()) {
            if (QWidget *childWidget = qobject_cast<QWidget*>(child)) {
                // Skip the timer (it's not a widget) - only consider actual widgets
                maxChildSize = maxChildSize.expandedTo(childWidget->sizeHint());
            }
        }
        if (!maxChildSize.isEmpty()) {
            resize(maxChildSize + QSize(borderWidth * 2, borderWidth * 2));
        }
    }
}