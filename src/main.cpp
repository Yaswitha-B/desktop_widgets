#include <QApplication>
#include "MainWidget.h"
#include "ColorWidget.h"
#include "DigitalClockWidget.h"
#include "ToDoListWidget.h"
#include "SettingsWidget.h"
#include "CalendarWidget.h"
#include "StickyNoteWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget mainWindow;
    mainWindow.show();

    auto settingsWidget = new SettingsWidget(&mainWindow);
    settingsWidget->setGeometry(900, 100, 60, 60);
    settingsWidget->show();

    auto calendarWidget = new CalendarWidget(&mainWindow);
    calendarWidget->setGeometry(550, 100, 300, 400);;
    calendarWidget->show();

    auto stickyNote = new StickyNoteWidget(&mainWindow);
    stickyNote->resize(350, 350); 
    stickyNote->move(mainWindow.width() - stickyNote->width() - 30, 60); 
    stickyNote->show();

    return app.exec();
}
