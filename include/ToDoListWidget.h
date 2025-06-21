#pragma once

#include "BaseWidget.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QCheckBox>
#include <QLabel>
#include <QEvent>

class ToDoListWidget : public BaseWidget {
    Q_OBJECT

public:
    explicit ToDoListWidget(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void addTask();
    void removeTask(QWidget *taskWidget);
    void toggleTaskState(QCheckBox *checkbox, QLabel *label);

private:
    QVBoxLayout *taskLayout;
    QLineEdit *taskInput;
};
