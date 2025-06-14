#include <QApplication>
#include <QWidget>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::cout << "App started!" << std::endl;

    QWidget window;
    window.setWindowTitle("Overlay Example");
    window.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    window.resize(400, 300);
    window.show();

    return app.exec();
}
