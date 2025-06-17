#pragma once

#include <QWidget>
#include <QScreen>
#include <QApplication>

class MainWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
protected:
    void paintEvent(QPaintEvent *event) override;

};

