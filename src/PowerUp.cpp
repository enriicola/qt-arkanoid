#include "PowerUp.h"

PowerUp::PowerUp(qreal x, qreal y, PowerUpType type)
    : m_position(x, y), m_width(40.0), m_height(20.0), m_speed(100.0), 
      m_type(type), m_active(true)
{
    switch (type) {
        case PowerUpType::BiggerPaddle:
            m_color = QColor(100, 255, 100);
            break;
        case PowerUpType::SmallerPaddle:
            m_color = QColor(255, 100, 100);
            break;
        case PowerUpType::SlowBall:
            m_color = QColor(100, 200, 255);
            break;
        case PowerUpType::FastBall:
            m_color = QColor(255, 200, 100);
            break;
        case PowerUpType::ExtraLife:
            m_color = QColor(255, 100, 255);
            break;
    }
}

void PowerUp::move(qreal delta)
{
    m_position.setY(m_position.y() + m_speed * delta);
}

QRectF PowerUp::rect() const
{
    return QRectF(m_position.x(), m_position.y(), m_width, m_height);
}

QString PowerUp::name() const
{
    switch (m_type) {
        case PowerUpType::BiggerPaddle:
            return "Bigger Paddle";
        case PowerUpType::SmallerPaddle:
            return "Smaller Paddle";
        case PowerUpType::SlowBall:
            return "Slow Ball";
        case PowerUpType::FastBall:
            return "Fast Ball";
        case PowerUpType::ExtraLife:
            return "Extra Life";
    }
    return "";
}
