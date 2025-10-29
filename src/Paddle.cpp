#include "Paddle.h"

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height)
    : m_position(x, y), m_width(width), m_height(height), m_speed(400.0)
{
}

void Paddle::moveLeft(qreal delta)
{
    m_position.setX(m_position.x() - m_speed * delta);
}

void Paddle::moveRight(qreal delta)
{
    m_position.setX(m_position.x() + m_speed * delta);
}

void Paddle::setPosition(qreal x, qreal y)
{
    m_position = QPointF(x, y);
}

void Paddle::constrainToBounds(qreal minX, qreal maxX)
{
    if (m_position.x() < minX) {
        m_position.setX(minX);
    }
    if (m_position.x() + m_width > maxX) {
        m_position.setX(maxX - m_width);
    }
}

QRectF Paddle::rect() const
{
    return QRectF(m_position.x(), m_position.y(), m_width, m_height);
}
