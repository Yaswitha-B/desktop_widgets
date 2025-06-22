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
    explicit StickyNoteWidget(QWidget *parent, const QString &uniqueId);
    QString getUniqueId() const;
    void setUniqueId(const QString &id);
    QVariantMap noteData() const;                    
    void loadNoteData(const QVariantMap &data);      

signals:
    void changed(); 

private slots:
    void chooseColor();       
    void onTextChanged();     

private:
    void updateBackgroundColor();  
    QString m_uniqueId;
    QLineEdit *titleEdit;
    QTextEdit *noteEdit;
    QColor backgroundColor;
};
