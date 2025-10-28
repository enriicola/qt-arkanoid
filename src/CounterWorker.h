#pragma once

#include <QObject>

class QTimer;

class CounterWorker : public QObject {
    Q_OBJECT

public:
    explicit CounterWorker(QObject *parent = nullptr);

public slots:
    void start();
    void stop();
    void setInterval(int intervalMs);

signals:
    void tick();
    void runningChanged(bool running);

private:
    QTimer *m_timer = nullptr;
};
