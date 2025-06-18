#include "ToDoListWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ToDoListWidget::ToDoListWidget(QWidget *parent)
    : BaseWidget(parent)
{
    input = new QLineEdit(this);
    input->setPlaceholderText("What's on your mind?");
    input->setMinimumHeight(30);
    input->setFont(QFont("Arial", 12));

    addButton = new QPushButton("Add Task", this);
    addButton->setMinimumHeight(30);

    taskList = new QListWidget(this);
    taskList->setSpacing(10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout();

    topLayout->addWidget(input);
    topLayout->addWidget(addButton);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(taskList);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &ToDoListWidget::addTask);

    loadTasksFromFile();
}

ToDoListWidget::~ToDoListWidget()
{
    saveTasksToFile();
}

void ToDoListWidget::addTask()
{
    QString text = input->text().trimmed();
    if (!text.isEmpty()) {
        createTaskItem(text);
        input->clear();
        saveTasksToFile();
    }
}

void ToDoListWidget::createTaskItem(const QString &taskText, bool initializing)
{
    QWidget *itemWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(itemWidget);
    layout->setContentsMargins(10, 5, 10, 5);

    QLabel *label = new QLabel(taskText);
    label->setFont(QFont("Arial", 14));
    label->setWordWrap(true);
    label->setMinimumHeight(30);

    QPushButton *removeButton = new QPushButton("❌");
    removeButton->setFixedSize(30, 30);
    removeButton->setToolTip("Remove Task");

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(removeButton);

    itemWidget->setLayout(layout);
    QListWidgetItem *item = new QListWidgetItem(taskList);
    item->setSizeHint(QSize(0, 50));
    taskList->setItemWidget(item, itemWidget);

    connect(removeButton, &QPushButton::clicked, this, [=]() {
        removeTaskItem(itemWidget);
        saveTasksToFile();
    });

    if (!initializing)
        saveTasksToFile();
}

void ToDoListWidget::removeTaskItem(QWidget *itemWidget)
{
    for (int i = 0; i < taskList->count(); ++i) {
        QListWidgetItem *item = taskList->item(i);
        if (taskList->itemWidget(item) == itemWidget) {
            delete taskList->takeItem(i);
            return;
        }
    }
}

void ToDoListWidget::saveTasksToFile()
{
    QFile file("tasks.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < taskList->count(); ++i) {
            QWidget *itemWidget = taskList->itemWidget(taskList->item(i));
            QLabel *label = itemWidget->findChild<QLabel *>();
            if (label)
                out << label->text() << "\n";
        }
        file.close();
    }
}

void ToDoListWidget::loadTasksFromFile()
{
    QFile file("tasks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                createTaskItem(line, true);
            }
        }
        file.close();
    }
}
