#include <QApplication>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

class CounterWindow : public QWidget {
public:
    explicit CounterWindow(QWidget *parent = nullptr)
        : QWidget(parent)
        , m_displayLabel(new QLabel(this))
    {
        setWindowTitle("Counter App");
        setMinimumSize(320, 200);

        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(24, 24, 24, 24);
        layout->setSpacing(16);

        auto *helloLabel = new QLabel("Hello, Qt!", this);
        helloLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(helloLabel);

        m_displayLabel->setAlignment(Qt::AlignCenter);

        QFont displayFont = m_displayLabel->font();
        displayFont.setPointSize(24);
        m_displayLabel->setFont(displayFont);

        layout->addWidget(m_displayLabel);

        auto *buttonsRow = new QHBoxLayout();
        buttonsRow->setSpacing(12);

        auto *plusButton = new QPushButton("+1", this);
        auto *minusButton = new QPushButton("-1", this);
        auto *resetButton = new QPushButton("Reset", this);

        buttonsRow->addWidget(minusButton);
        buttonsRow->addWidget(resetButton);
        buttonsRow->addWidget(plusButton);

        layout->addLayout(buttonsRow);

        auto *quitButton = new QPushButton("Quit", this);
        quitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        auto *quitRow = new QHBoxLayout();
        quitRow->addStretch();
        quitRow->addWidget(quitButton);
        quitRow->addStretch();
        layout->addLayout(quitRow);

        layout->addStretch();

        connect(plusButton, &QPushButton::clicked, this, [this]() {
            adjustCount(+1);
        });
        connect(minusButton, &QPushButton::clicked, this, [this]() {
            adjustCount(-1);
        });
        connect(resetButton, &QPushButton::clicked, this, [this]() {
            resetCount();
        });
        connect(quitButton, &QPushButton::clicked, this, &QWidget::close);

        updateDisplay();
    }

private:
    QLabel *m_displayLabel = nullptr;
    int m_count = 0;

    void adjustCount(int delta)
    {
        m_count += delta;
        updateDisplay();
    }

    void resetCount()
    {
        m_count = 0;
        updateDisplay();
    }

    void updateDisplay()
    {
        m_displayLabel->setText(QString("Count: %1").arg(m_count));
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationDisplayName("Counter");

    CounterWindow counter;
    counter.show();

    return app.exec();
}
