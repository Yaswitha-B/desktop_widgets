#include "ToDoListWidget.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

ToDoListWidget::ToDoListWidget(QWidget *parent) : BaseWidget(parent) {
    setFixedSize(300, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    taskInput = new QLineEdit();
    taskInput->setPlaceholderText("Enter a task...");
    taskInput->setStyleSheet("padding: 6px;");
    QPushButton *addButton = new QPushButton("Add");
    connect(addButton, &QPushButton::clicked, this, static_cast<void (ToDoListWidget::*)()>(&ToDoListWidget::addTask));
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

    loadTasks(); 
}

void ToDoListWidget::addTask(const QString &text, bool completed) {
    QString taskText = text.isEmpty() ? taskInput->text().trimmed() : text;
    if (taskText.isEmpty()) return;

    QWidget *taskWidget = new QWidget();
    taskWidget->setStyleSheet("padding: 8px;");
    QHBoxLayout *layout = new QHBoxLayout(taskWidget);

    QCheckBox *checkbox = new QCheckBox();
    checkbox->setChecked(completed);

    QLabel *label = new QLabel(taskText);
    label->setStyleSheet(completed ?
        "text-decoration: line-through; color: gray;" :
        "font-size: 14px;");

    layout->addWidget(checkbox);
    layout->addWidget(label);
    layout->addStretch();

    taskLayout->addWidget(taskWidget);
    if (text.isEmpty()) taskInput->clear();

    connect(checkbox, &QCheckBox::stateChanged, this, [=]() {
        toggleTaskState(checkbox, label);
        saveTasks();  
    });

    taskWidget->installEventFilter(this);
    saveTasks(); 
}

void ToDoListWidget::addTask() {
    addTask("", false);
}

void ToDoListWidget::toggleTaskState(QCheckBox *checkbox, QLabel *label) {
    if (checkbox->isChecked()) {
        label->setStyleSheet("text-decoration: line-through; color: gray;");
    } else {
        label->setStyleSheet("font-size: 14px; color: black;");
    }
    saveTasks();
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
    saveTasks();  
}

void ToDoListWidget::saveTasks() {
    QFile file("tasks.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < taskLayout->count(); ++i) {
            QWidget *taskWidget = taskLayout->itemAt(i)->widget();
            if (!taskWidget) continue;

            QCheckBox *checkbox = taskWidget->findChild<QCheckBox *>();
            QLabel *label = taskWidget->findChild<QLabel *>();
            if (checkbox && label) {
                out << checkbox->isChecked() << "|" << label->text() << "\n";
            }
        }
        file.close();
    }
}

void ToDoListWidget::loadTasks() {
    QFile file("tasks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() == 2) {
                bool completed = parts[0] == "1";
                QString task = parts[1];
                addTask(task, completed);
            }
        }
        file.close();
    }
}
