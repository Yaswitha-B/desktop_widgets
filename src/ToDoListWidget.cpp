#include "ToDoListWidget.h"

ToDoListWidget::ToDoListWidget(QWidget *parent) : BaseWidget(parent) {
    setFixedSize(300, 400);
    // setStyleSheet("background-color: #eeeeee;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    taskInput = new QLineEdit();
    taskInput->setPlaceholderText("Enter a task...");
    taskInput->setStyleSheet("padding: 6px;");
    QPushButton *addButton = new QPushButton("Add");
    connect(addButton, &QPushButton::clicked, this, &ToDoListWidget::addTask);
    inputLayout->addWidget(taskInput);
    inputLayout->addWidget(addButton);

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
    taskWidget->setStyleSheet("padding: 8px;");
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

    taskWidget->installEventFilter(this);
}

void ToDoListWidget::toggleTaskState(QCheckBox *checkbox, QLabel *label) {
    if (checkbox->isChecked()) {
        label->setStyleSheet("text-decoration: line-through; color: gray;");
    } else {
        label->setStyleSheet("text-decoration: none; color: black;");
    }
}

bool ToDoListWidget::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        QWidget *taskWidget = qobject_cast<QWidget *>(watched);
        if (taskWidget) {
            removeTask(taskWidget);
            return true;
        }
    }
    return BaseWidget::eventFilter(watched, event);
}

void ToDoListWidget::removeTask(QWidget *taskWidget) {
    taskLayout->removeWidget(taskWidget);
    taskWidget->deleteLater();
}
