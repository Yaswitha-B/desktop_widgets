#include "ImageWidget.h"
#include "WidgetManager.h"
#include <QSettings>
#include <QFileDialog>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>
#include <QDir>

ImageWidget::ImageWidget(QWidget *parent, const QString &id)
    : BaseWidget(parent), resizeMode(false), resizing(false)
{
    uniqueId = id.isEmpty() ? QUuid::createUuid().toString(QUuid::WithoutBraces) : id;
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(minWidgetSize, minWidgetSize);
    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("border-radius: 12px; background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f8fafc, stop:1 #e0e7ef);");

    changeImageButton = new QPushButton("\U0001F5BC Change", this);
    resizeModeButton = new QPushButton("\U0001F5D1 Resize", this);
    connect(resizeModeButton, &QPushButton::clicked, this, &ImageWidget::onToggleResizeMode);
    connect(changeImageButton, &QPushButton::clicked, this, &ImageWidget::onChangeImage);
    changeImageButton->setFocusPolicy(Qt::NoFocus);
    resizeModeButton->setFocusPolicy(Qt::NoFocus);
    changeImageButton->setStyleSheet("QPushButton { background: #4f8cff; color: white; border-radius: 8px; padding: 4px 12px; font-weight: bold; } QPushButton:hover { background: #357ae8; }");
    resizeModeButton->setStyleSheet("QPushButton { background: #e0e7ef; color: #222; border-radius: 8px; padding: 4px 12px; font-weight: bold; } QPushButton:hover { background: #b6c6e3; }");

    headerWidget = new QWidget(this);
    headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(8, 8, 8, 8);
    headerLayout->setSpacing(8);
    headerLayout->addWidget(changeImageButton);
    headerLayout->addWidget(resizeModeButton);
    headerLayout->addStretch();
    headerWidget->setLayout(headerLayout);
    headerWidget->setStyleSheet("background: rgba(255,255,255,0.85); border-bottom: 1px solid #e0e7ef; border-top-left-radius: 12px; border-top-right-radius: 12px;");

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(imageLabel);
    setLayout(mainLayout);

    setMinimumSize(minWidgetSize, minWidgetSize + headerWidget->height());
    // setStyleSheet("QWidget { border-radius: 12px; background: #f8fafc; }");
    loadState();
}

ImageWidget::~ImageWidget() {
    // saveState();
}

void ImageWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        onChangeImage();
    }
    BaseWidget::mouseDoubleClickEvent(event);
}

void ImageWidget::onChangeImage() {
    QString file = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath(), "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    if (!file.isEmpty()) {
        setImage(file);
        saveState();
    }
}

void ImageWidget::setImage(const QString &path) {
    imagePath = path;
    QPixmap pix(path);
    imageLabel->setPixmap(pix);
}

void ImageWidget::onToggleResizeMode() {
    resizeMode = !resizeMode;
    if (resizeMode) {
        resizeModeButton->setText("\U0001F5D1 Drag");
        setCursor(Qt::SizeFDiagCursor);
    } else {
        resizeModeButton->setText("\U0001F5D1 Resize");
        setCursor(Qt::ArrowCursor);
    }
}

void ImageWidget::mousePressEvent(QMouseEvent *event) {
    if (resizeMode && event->button() == Qt::LeftButton) {
        resizing = true;
        resizeStartPos = event->globalPosition().toPoint();
        resizeStartSize = size();
        event->accept();
        return;
    }
    BaseWidget::mousePressEvent(event);
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event) {
    if (resizeMode && resizing && (event->buttons() & Qt::LeftButton)) {
        QPoint delta = event->globalPosition().toPoint() - resizeStartPos;
        int newWidth = qMax(minWidgetSize, resizeStartSize.width() + delta.x());
        int newHeight = qMax(minWidgetSize, resizeStartSize.height() + delta.y());
        resize(newWidth, newHeight);
        event->accept();
        return;
    }
    BaseWidget::mouseMoveEvent(event);
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (resizeMode && resizing && event->button() == Qt::LeftButton) {
        resizing = false;
        saveState();
        WidgetManager::instance().saveWidgets();
        event->accept();
        return;
    }
    BaseWidget::mouseReleaseEvent(event);
}

void ImageWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    // imageLabel->setFixedSize(width(), height() - headerWidget->height());
    // Let the layout handle resizing
}

void ImageWidget::loadState() {
    QSettings settings;
    settings.beginGroup("ImageWidget_" + uniqueId);
    imagePath = settings.value("imagePath", "").toString();
    if (!imagePath.isEmpty()) {
        setImage(imagePath);
    }
    QRect geom = settings.value("geometry", QRect(200, 200, 300, 300)).toRect();
    setGeometry(geom);
    settings.endGroup();
}

void ImageWidget::saveState() const {
    QSettings settings;
    settings.beginGroup("ImageWidget_" + uniqueId);
    settings.setValue("imagePath", imagePath);
    settings.setValue("geometry", geometry());
    settings.endGroup();
}

QString ImageWidget::getUniqueId() const {
    return uniqueId;
}

void ImageWidget::setUniqueId(const QString &id) {
    uniqueId = id;
}

QString ImageWidget::getImagePath() const {
    return imagePath;
}