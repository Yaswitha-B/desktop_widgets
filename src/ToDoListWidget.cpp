#include "ToDoListWidget.h"

ToDoListWidget::ToDoListWidget(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: #eeeeee; border-radius: 20px;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Input
    QHBoxLayout *inputLayout = new QHBoxLayout();
    taskInput = new QLineEdit();
    taskInput->setPlaceholderText("Enter a task...");
    taskInput->setStyleSheet("border-radius: 15px; padding: 6px;");

    QPushButton *addButton = new QPushButton("Add");
    connect(addButton, &QPushButton::clicked, this, &ToDoListWidget::addTask);
    inputLayout->addWidget(taskInput);
    inputLayout->addWidget(addButton);

    // Task list container
    QWidget *taskContainer = new QWidget();
    taskLayout = new QVBoxLayout(taskContainer);
    taskLayout->setAlignment(Qt::AlignTop);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(taskContainer);
    scrollArea->setStyleSheet("border: none;");

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(scrollArea);
}

void ToDoListWidget::addTask() {
    QString taskText = taskInput->text().trimmed();
    if (taskText.isEmpty()) return;

    QWidget *taskWidget = new QWidget();
    taskWidget->setStyleSheet("background-color: white; border-radius: 15px; padding: 8px;");
    QHBoxLayout *layout = new QHBoxLayout(taskWidget);

    QCheckBox *checkbox = new QCheckBox();
    QLabel *label = new QLabel(taskText);
    label->setStyleSheet("font-size: 14px;");

    layout->addWidget(checkbox);
    layout->addWidget(label);
    layout->addStretch();

    taskLayout->addWidget(taskWidget);
    taskInput->clear();

    connect(checkbox, &QCheckBox::stateChanged, this, [=]() {
        toggleTaskState(checkbox, label);
    });

    // Double-click delete
    taskWidget->installEventFilter(this);
    connect(taskWidget, &QWidget::destroyed, [=]() {
        taskWidget->deleteLater();
    });
}

// Strike-through toggle
void ToDoListWidget::toggleTaskState(QCheckBox *checkbox, QLabel *label) {
    if (checkbox->isChecked()) {
        label->setStyleSheet("text-decoration: line-through; color: gray;");
    } else {
        label->setStyleSheet("text-decoration: none; color: black;");
    }
}

// Override event filter to detect double-click on task
bool ToDoListWidget::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        QWidget *taskWidget = qobject_cast<QWidget *>(watched);
        if (taskWidget) {
            removeTask(taskWidget);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

// Remove task
void ToDoListWidget::removeTask(QWidget *taskWidget) {
    taskLayout->removeWidget(taskWidget);
    taskWidget->deleteLater();
}
