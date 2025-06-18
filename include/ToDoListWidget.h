#pragma once

#include "BaseWidget.h"
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>

class ToDoListWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit ToDoListWidget(QWidget *parent = nullptr);
    ~ToDoListWidget();

private slots:
    void addTask();
    void removeTaskItem(QWidget *itemWidget);
    void loadTasksFromFile();
    void saveTasksToFile();

private:
    QLineEdit *input;
    QPushButton *addButton;
    QListWidget *taskList;

    void createTaskItem(const QString &taskText, bool initializing = false);
};
