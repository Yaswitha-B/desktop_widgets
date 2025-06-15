#include <QApplication>
#include "MainWidget.h"
#include "ColorWidget.h"
#include "DigitalClockWidget.h"  // Include the header

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget mainWindow;
    mainWindow.show();

    // Existing ColorWidget
    ColorWidget *colorWidget = new ColorWidget(&mainWindow);
    colorWidget->setGeometry(100, 100, 150, 150);
    colorWidget->show();

    // New DigitalClockWidget
    DigitalClockWidget *clockWidget = new DigitalClockWidget(&mainWindow);
    clockWidget->setGeometry(300, 100, 200, 100); // Adjust size and position as needed
    clockWidget->show();

    return app.exec();
}
