#include <QApplication>
#include "MainWidget.h"
#include "ColorWidget.h"
#include "DigitalClockWidget.h"
#include "ToDoListWidget.h"
#include "SettingsWidget.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget mainWindow;
    mainWindow.show();
    
    auto settingsWidget = new SettingsWidget(&mainWindow);
    settingsWidget->setGeometry(900, 100, 60, 60);
    settingsWidget->show();
    
    return app.exec();
}
