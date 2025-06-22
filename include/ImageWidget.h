#pragma once
#include "BaseWidget.h"
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QSettings>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QFileDialog>
#include <QUuid>

class ImageWidget : public BaseWidget {
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr, const QString &uniqueId = QString());
    ~ImageWidget() override;

    void loadState();
    void saveState() const;
    QString getUniqueId() const;
    void setUniqueId(const QString &id);
    QString getImagePath() const;
    void setImage(const QString &path);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onChangeImage();
    void onToggleResizeMode();

private:
    void updateHeader();
    void enterResizeMode();
    void exitResizeMode();
    void updateResizeCursor(const QPoint &pos);

    QLabel *imageLabel;
    QPushButton *changeImageButton;
    QPushButton *resizeModeButton;
    QWidget *headerWidget;
    QHBoxLayout *headerLayout;
    QVBoxLayout *mainLayout;

    QString imagePath;
    QString uniqueId;
    bool resizeMode;
    bool resizing;
    QPoint resizeStartPos;
    QSize resizeStartSize;

    static constexpr int minWidgetSize = 100;
};