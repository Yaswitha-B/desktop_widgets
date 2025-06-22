#include "WidgetManagerDialog.h"
#include "WidgetManager.h"
#include <QMenu>
#include <QMessageBox>
#include <QCursor>
#include <QFont>

WidgetManagerDialog::WidgetManagerDialog(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Widget Manager");
    setupUI();
    loadConfiguration();

    setStyleSheet(R"(
        QWidget {
            background-color: #f5f7fa; /* light grey background */
            font-family: 'Segoe UI', 'Arial', sans-serif;
            font-size: 14px;
            color: #333;
        }
        QListWidget {
            background-color: #ffffff;
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 6px;
        }
        QPushButton {
            background-color: #2196F3; /* blue button */
            color: white;
            border: none;
            padding: 8px 12px;
            border-radius: 6px;
        }
        QPushButton:hover {
            background-color: #1976D2;
        }
        QPushButton:pressed {
            background-color: #1565C0;
        }
    )");
}

void WidgetManagerDialog::setupUI() {
    auto layout = new QVBoxLayout(this);

    m_widgetList = new QListWidget(this);
    m_widgetList->setSpacing(5);
    layout->addWidget(m_widgetList);

    auto buttonLayout = new QHBoxLayout();

    m_addButton = new QPushButton("Add Widget", this);
    m_addButton->setMinimumHeight(36);
    connect(m_addButton, &QPushButton::clicked, this, &WidgetManagerDialog::addWidget);
    buttonLayout->addWidget(m_addButton);

    m_removeButton = new QPushButton("Remove Widget", this);
    m_removeButton->setMinimumHeight(36);
    connect(m_removeButton, &QPushButton::clicked, this, &WidgetManagerDialog::removeSelectedWidget);
    buttonLayout->addWidget(m_removeButton);

    m_saveButton = new QPushButton("Save", this);
    m_saveButton->setMinimumHeight(36);
    connect(m_saveButton, &QPushButton::clicked, this, &WidgetManagerDialog::saveConfiguration);
    buttonLayout->addWidget(m_saveButton);

    layout->addLayout(buttonLayout);

    setMinimumSize(350, 450);
}

void WidgetManagerDialog::addWidget() {
    QMenu menu(this);
    menu.addAction("Color Widget", [this]() { createNewWidget("ColorWidget"); });
    menu.addAction("Digital Clock", [this]() { createNewWidget("DigitalClockWidget"); });
    menu.addAction("ToDo List", [this]() { createNewWidget("ToDoListWidget"); });
    menu.addAction("Calendar", [this]() { createNewWidget("CalendarWidget"); });
    menu.addAction("Sticky Notes", [this]() { createNewWidget("StickyNoteWidget"); });
    menu.exec(QCursor::pos());
}

void WidgetManagerDialog::createNewWidget(const QString& type) {
    QWidget* overlay = parentWidget();
    QPoint pos = QCursor::pos() - overlay->mapToGlobal(QPoint(0,0));
    WidgetManager::instance().addWidget(type, overlay, pos);
    loadConfiguration();
}

void WidgetManagerDialog::removeSelectedWidget() {
    auto item = m_widgetList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Warning", "Please select a widget to remove.");
        return;
    }

    auto widgets = WidgetManager::instance().getWidgets();
    int index = m_widgetList->row(item);
    if (index >= 0 && index < widgets.size()) {
        WidgetManager::instance().removeWidget(widgets[index]);
        loadConfiguration();
    }
}

void WidgetManagerDialog::loadConfiguration() {
    m_widgetList->clear();
    for (auto widget : WidgetManager::instance().getWidgets()) {
        QString type = widget->metaObject()->className();
        QString pos = QString::number(widget->x()) + ", " + QString::number(widget->y());
        m_widgetList->addItem(QString("%1 at (%2)").arg(type).arg(pos));
    }
}

void WidgetManagerDialog::saveConfiguration() {
    WidgetManager::instance().saveWidgets();
    QMessageBox::information(this, "Success", "Widget configuration saved successfully.");
}
