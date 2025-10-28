#pragma once

#include <QObject>
#include <QThread>
#include <QString>

class CounterWorker;

class AppState : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString greeting READ greeting CONSTANT)
    Q_PROPERTY(int counter READ counter NOTIFY counterChanged)
    Q_PROPERTY(bool autoRunning READ autoRunning NOTIFY autoRunningChanged)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

public:
    explicit AppState(QObject *parent = nullptr);
    ~AppState() override;

    QString greeting() const;
    int counter() const;
    bool autoRunning() const;
    int interval() const;

    Q_INVOKABLE void increment();
    Q_INVOKABLE void decrement();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void startAutoIncrement();
    Q_INVOKABLE void stopAutoIncrement();
    Q_INVOKABLE void setInterval(int intervalMs);

signals:
    void counterChanged();
    void autoRunningChanged();
    void intervalChanged();

private:
    void handleWorkerTick();
    void updateAutoRunning(bool running);

    int m_counter = 0;
    bool m_autoRunning = false;
    int m_intervalMs = 500;

    CounterWorker *m_worker = nullptr;
    QThread m_workerThread;
};
