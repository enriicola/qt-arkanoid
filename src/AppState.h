#pragma once

#include <QObject>
#include <QString>

class AppState : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString greeting READ greeting CONSTANT)
    Q_PROPERTY(int counter READ counter NOTIFY counterChanged)

public:
    explicit AppState(QObject *parent = nullptr);

    QString greeting() const;
    int counter() const;

    Q_INVOKABLE void increment();
    Q_INVOKABLE void decrement();
    Q_INVOKABLE void reset();

signals:
    void counterChanged();

private:
    int m_counter = 0;
};
