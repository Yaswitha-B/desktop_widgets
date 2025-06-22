#pragma once

#include "BaseWidget.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QColor>
#include <QVariantMap>

class StickyNoteWidget : public BaseWidget {
    Q_OBJECT

public:
    explicit StickyNoteWidget(QWidget *parent = nullptr);

    QVariantMap noteData() const;                    // For WidgetManager save
    void loadNoteData(const QVariantMap &data);      // For WidgetManager load

signals:
    void changed();  // 👉 Notify WidgetManager to trigger save

private slots:
    void chooseColor();       // Open color dialog
    void onTextChanged();     // Triggered by text edits

private:
    void updateBackgroundColor();  // Apply selected color

    QLineEdit *titleEdit;
    QTextEdit *noteEdit;
    QColor backgroundColor;
};
