#pragma once

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class WidgetManagerDialog : public QDialog {
    Q_OBJECT
public:
    explicit WidgetManagerDialog(QWidget* parent = nullptr);

private slots:
    void addWidget();
    void removeSelectedWidget();
    void saveConfiguration();

private:
    void setupUI();
    void loadConfiguration();
    void createNewWidget(const QString& type);

    QListWidget* m_widgetList;
    QPushButton* m_addButton;
    QPushButton* m_removeButton;
    QPushButton* m_saveButton;
};

