#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Counter App");
    window.resize(300, 150);

    int count = 0;

    QLabel *displayLabel = new QLabel("Count: 0", &window);
    displayLabel->resize(200, 30);
    displayLabel->move(50, 20);
    displayLabel->setAlignment(Qt::AlignCenter);

    QPushButton *plusButton = new QPushButton("+1", &window);
    plusButton->resize(60, 30);
    plusButton->move(60, 70);

    QPushButton *minusButton = new QPushButton("-1", &window);
    minusButton->resize(60, 30);
    minusButton->move(130, 70);

    QPushButton *resetButton = new QPushButton("Reset", &window);
    resetButton->resize(60, 30);
    resetButton->move(200, 70);

    QPushButton *quitButton = new QPushButton("Quit", &window);
    quitButton->resize(80, 30);
    quitButton->move(110, 110);

    auto updateDisplay = [&]() {
        displayLabel->setText(QString("Count: %1").arg(count));
    };

    QObject::connect(plusButton, &QPushButton::clicked, [&]() {
        count++;
        updateDisplay();
    });

    QObject::connect(minusButton, &QPushButton::clicked, [&]() {
        count--;
        updateDisplay();
    });

    QObject::connect(resetButton, &QPushButton::clicked, [&]() {
        count = 0;
        updateDisplay();
    });

    QObject::connect(quitButton, &QPushButton::clicked, &app, &QApplication::quit);

    window.show();

    return app.exec();
}