#include <QApplication>
#include "MainWidget.h"
#include "ColorWidget.h"
#include "DigitalClockWidget.h"
#include "ToDoListWidget.h"
#include "CalendarWidget.h"
#include "StickyNoteWidget.h"

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

    auto todoWidget = new ToDoListWidget(&mainWindow);
    todoWidget->setGeometry(550, 100, 300, 400);
    todoWidget->show();

    auto calendarWidget = new CalendarWidget(&mainWindow);
    calendarWidget->setGeometry(550, 100, 300, 400);;
    calendarWidget->show();

    auto stickyNote = new StickyNoteWidget(&mainWindow);
    stickyNote->resize(350, 350); 
    stickyNote->move(mainWindow.width() - stickyNote->width() - 30, 60); 
    stickyNote->show();

    return app.exec();
}
