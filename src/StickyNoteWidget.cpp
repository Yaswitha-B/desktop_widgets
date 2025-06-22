#include "StickyNoteWidget.h"
#include <QColorDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

StickyNoteWidget::StickyNoteWidget(QWidget *parent)
    : BaseWidget(parent), backgroundColor(QColor("#44475a")), m_uniqueId("")
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(300, 300);
    setBorderWidth(6);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    titleEdit = new QLineEdit();
    titleEdit->setStyleSheet("font-weight: bold; font-size: 16px; padding: 4px;");
    layout->addWidget(titleEdit);
    noteEdit = new QTextEdit();
    noteEdit->setPlaceholderText("Write your note here...");
    noteEdit->setStyleSheet("font-size: 14px; padding: 6px;");
    layout->addWidget(noteEdit);
    QPushButton *colorButton = new QPushButton("Change Color 🎨");
    colorButton->setStyleSheet("padding: 6px; font-size: 13px;");
    layout->addWidget(colorButton);
    connect(colorButton, &QPushButton::clicked, this, &StickyNoteWidget::chooseColor);
    connect(titleEdit, &QLineEdit::textChanged, this, &StickyNoteWidget::onTextChanged);
    connect(noteEdit, &QTextEdit::textChanged, this, &StickyNoteWidget::onTextChanged);
    updateBackgroundColor();
}

StickyNoteWidget::StickyNoteWidget(QWidget *parent, const QString &uniqueId)
    : BaseWidget(parent), m_uniqueId(uniqueId), backgroundColor(QColor("#44475a")) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(300, 300);
    setBorderWidth(6);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    titleEdit = new QLineEdit();
    titleEdit->setStyleSheet("font-weight: bold; font-size: 16px; padding: 4px;");
    layout->addWidget(titleEdit);
    noteEdit = new QTextEdit();
    noteEdit->setPlaceholderText("Write your note here...");
    noteEdit->setStyleSheet("font-size: 14px; padding: 6px;");
    layout->addWidget(noteEdit);
    QPushButton *colorButton = new QPushButton("Change Color 🎨");
    colorButton->setStyleSheet("padding: 6px; font-size: 13px;");
    layout->addWidget(colorButton);
    connect(colorButton, &QPushButton::clicked, this, &StickyNoteWidget::chooseColor);
    connect(titleEdit, &QLineEdit::textChanged, this, &StickyNoteWidget::onTextChanged);
    connect(noteEdit, &QTextEdit::textChanged, this, &StickyNoteWidget::onTextChanged);
    updateBackgroundColor();
}

QString StickyNoteWidget::getUniqueId() const {
    return m_uniqueId;
}

void StickyNoteWidget::setUniqueId(const QString &id) {
    m_uniqueId = id;
}

QVariantMap StickyNoteWidget::noteData() const {
    QVariantMap data;
    data["title"] = titleEdit->text();
    data["content"] = noteEdit->toPlainText();
    data["color"] = backgroundColor.name();
    data["uniqueId"] = m_uniqueId;
    return data;
}

void StickyNoteWidget::loadNoteData(const QVariantMap &data) {
    if (data.contains("title"))
        titleEdit->setText(data.value("title").toString());
    else
        titleEdit->setText("Untitled Note");
    noteEdit->setText(data.value("content").toString());
    if (data.contains("color"))
        backgroundColor = QColor(data.value("color").toString());
    else
        backgroundColor = QColor("#44475a");
    if (data.contains("uniqueId"))
        m_uniqueId = data.value("uniqueId").toString();
    updateBackgroundColor();
}

void StickyNoteWidget::chooseColor() {
    QColor color = QColorDialog::getColor(backgroundColor, this, "Select Note Color");
    if (color.isValid()) {
        backgroundColor = color;
        updateBackgroundColor();
        emit changed();  
    }
}

void StickyNoteWidget::updateBackgroundColor() {
    QString style = QString("QWidget { background-color: %1; } ").arg(backgroundColor.name());
    setStyleSheet(style);
}

void StickyNoteWidget::onTextChanged() {
    emit changed(); 
}
