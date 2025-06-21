#include "StickyNoteWidget.h"

StickyNoteWidget::StickyNoteWidget(QWidget *parent)
    : BaseWidget(parent) {
    resize(300, 300);
    setupUI();
    applyStyle(QColor("#fff9c4"));
}

void StickyNoteWidget::setupUI() {
    noteText = new QTextEdit(this);
    noteText->setPlaceholderText("Write your note here...");
    noteText->setStyleSheet("border: none; background: transparent; font-size: 14px;");

    colorButton = new QPushButton("🎨", this);
    colorButton->setFixedSize(24, 24);
    connect(colorButton, &QPushButton::clicked, this, &StickyNoteWidget::changeColor);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addStretch();
    topLayout->addWidget(colorButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(noteText);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    setLayout(mainLayout);
}

void StickyNoteWidget::changeColor() {
    QColor color = QColorDialog::getColor(Qt::yellow, this, "Choose Note Color");
    if (color.isValid()) {
        applyStyle(color);
    }
}

void StickyNoteWidget::applyStyle(const QColor &color) {
    QString style = QString("background-color: %1;")
                        .arg(color.name());
    setStyleSheet(style);
}