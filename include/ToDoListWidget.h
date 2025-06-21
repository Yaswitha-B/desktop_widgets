#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QCheckBox>
#include <QLabel>
#include <QFrame>
#include <QMouseEvent>
#include <QEvent>  // Include this for QEvent

class ToDoListWidget : public QWidget {
    Q_OBJECT

public:
    explicit ToDoListWidget(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;  // <-- ADD THIS LINE

private slots:
    void addTask();
    void removeTask(QWidget *taskWidget);
    void toggleTaskState(QCheckBox *checkbox, QLabel *label);

private:
    QVBoxLayout *taskLayout;
    QLineEdit *taskInput;
};
