#include "AppState.h"

#include <QMetaObject>

#include <algorithm>

#include "CounterWorker.h"

namespace {
constexpr int kMinIntervalMs = 50;
constexpr int kMaxIntervalMs = 2500;
}

AppState::AppState(QObject *parent)
    : QObject(parent)
    , m_worker(new CounterWorker())
{
    m_workerThread.setObjectName(QStringLiteral("CounterWorkerThread"));
    m_worker->moveToThread(&m_workerThread);

    connect(&m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(m_worker, &CounterWorker::tick, this, &AppState::handleWorkerTick);
    connect(m_worker, &CounterWorker::runningChanged, this, &AppState::updateAutoRunning);

    m_workerThread.start();

    QMetaObject::invokeMethod(
        m_worker,
        "setInterval",
        Qt::QueuedConnection,
        Q_ARG(int, m_intervalMs));
}

AppState::~AppState()
{
    stopAutoIncrement();
    m_workerThread.quit();
    m_workerThread.wait();
}

QString AppState::greeting() const
{
    return QStringLiteral("Hello from a worker thread!");
}

int AppState::counter() const
{
    return m_counter;
}

bool AppState::autoRunning() const
{
    return m_autoRunning;
}

int AppState::interval() const
{
    return m_intervalMs;
}

void AppState::increment()
{
    m_counter += 1;
    emit counterChanged();
}

void AppState::decrement()
{
    m_counter -= 1;
    emit counterChanged();
}

void AppState::reset()
{
    if (m_counter == 0)
        return;

    m_counter = 0;
    emit counterChanged();
}

void AppState::startAutoIncrement()
{
    if (m_autoRunning || !m_worker)
        return;

    QMetaObject::invokeMethod(m_worker, "start", Qt::QueuedConnection);
}

void AppState::stopAutoIncrement()
{
    if (!m_worker)
        return;

    QMetaObject::invokeMethod(m_worker, "stop", Qt::QueuedConnection);
}

void AppState::setInterval(int intervalMs)
{
    intervalMs = std::clamp(intervalMs, kMinIntervalMs, kMaxIntervalMs);
    if (intervalMs == m_intervalMs)
        return;

    m_intervalMs = intervalMs;
    emit intervalChanged();

    if (!m_worker)
        return;

    QMetaObject::invokeMethod(
        m_worker,
        "setInterval",
        Qt::QueuedConnection,
        Q_ARG(int, m_intervalMs));
}

void AppState::handleWorkerTick()
{
    m_counter += 1;
    emit counterChanged();
}

void AppState::updateAutoRunning(bool running)
{
    if (m_autoRunning == running)
        return;

    m_autoRunning = running;
    emit autoRunningChanged();
}
