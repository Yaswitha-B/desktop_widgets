#pragma once

#include "BaseWidget.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColorDialog>

class StickyNoteWidget : public BaseWidget {
    Q_OBJECT

public:
    explicit StickyNoteWidget(QWidget *parent = nullptr);

private slots:
    void changeColor();

private:
    QTextEdit *noteText;
    QPushButton *colorButton;
    void setupUI();
    void applyStyle(const QColor &color);
};