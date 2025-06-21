#include <QApplication>
#include "MainWidget.h"
#include "SettingsWidget.h"
#include "WidgetManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget mainWindow;
    mainWindow.show();

    WidgetManager::instance().loadWidgets(&mainWindow);

    auto settingsWidget = new SettingsWidget(&mainWindow);
    settingsWidget->setGeometry(900, 100, 60, 60);
    settingsWidget->show();

    int result = app.exec();

    WidgetManager::instance().saveWidgets();
    return result;
}
