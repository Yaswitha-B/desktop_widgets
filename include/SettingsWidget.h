#pragma once
#include "BaseWidget.h"
#include <QPushButton>
#include <QDialog>
#include "WidgetManagerDialog.h"

class SettingsWidget : public BaseWidget {
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    WidgetManagerDialog *managerDialog;
};
