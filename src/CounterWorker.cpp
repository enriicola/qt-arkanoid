#include "CounterWorker.h"

#include <QTimer>

namespace {
constexpr int kDefaultIntervalMs = 500;
}

CounterWorker::CounterWorker(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
{
    m_timer->setInterval(kDefaultIntervalMs);
    m_timer->setTimerType(Qt::PreciseTimer);
    connect(m_timer, &QTimer::timeout, this, &CounterWorker::tick);
}

void CounterWorker::start()
{
    if (m_timer->isActive())
        return;

    m_timer->start();
    emit runningChanged(true);
}

void CounterWorker::stop()
{
    if (!m_timer->isActive())
        return;

    m_timer->stop();
    emit runningChanged(false);
}

void CounterWorker::setInterval(int intervalMs)
{
    if (intervalMs < 10)
        intervalMs = 10;

    const bool wasActive = m_timer->isActive();
    m_timer->stop();
    m_timer->setInterval(intervalMs);
    if (wasActive)
        m_timer->start();
}
