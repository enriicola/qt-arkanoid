#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Counter App");
    window.resize(200, 100);

    // Create a simple button
    QPushButton *button = new QPushButton("Click me!", &window);
    button->resize(100, 30);
    button->move(50, 35);  // Position it in the center

    window.show();

    return app.exec();
}