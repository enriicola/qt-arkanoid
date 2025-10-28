#include "AppState.h"

AppState::AppState(QObject *parent)
    : QObject(parent)
    , m_counter(0)
{
}

QString AppState::greeting() const
{
    return QStringLiteral("Hello from C++ via QML!");
}

int AppState::counter() const
{
    return m_counter;
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
