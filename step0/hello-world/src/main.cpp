#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel helloLabel("Hello, World!");
    helloLabel.setMinimumSize(240, 100);
    helloLabel.setAlignment(Qt::AlignCenter);
    helloLabel.show();

    return app.exec();
}
