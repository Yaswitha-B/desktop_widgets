#include <QApplication>
#include "MainWidget.h"
#include "ColorWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget mainWindow;
    mainWindow.show();

    ColorWidget *colorWidget = new ColorWidget(&mainWindow);
    colorWidget->setGeometry(100, 100, 150, 150);
    colorWidget->show();


    return app.exec();
}
