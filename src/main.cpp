#include <QApplication>
#include "MainWidget.h"
#include "ColorWidget.h"
#include "DigitalClockWidget.h"
#include "ToDoListWidget.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget mainWindow;
    mainWindow.show();

    auto colorWidget = new ColorWidget(&mainWindow);
    colorWidget->setGeometry(100, 100, 150, 150);
    colorWidget->show();

    auto clockWidget = new DigitalClockWidget(&mainWindow);
    clockWidget->setGeometry(300, 100, 200, 100);
    clockWidget->show();

    ToDoListWidget *todoWidget = new ToDoListWidget(&mainWindow);
    todoWidget->setGeometry(100, 300, 450, 500);  
    todoWidget->show();

    return app.exec();
}
