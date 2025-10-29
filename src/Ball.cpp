#include "Ball.h"
#include <cmath>

Ball::Ball(qreal x, qreal y, qreal radius)
    : m_position(x, y), m_velocity(200.0, -200.0), m_radius(radius)
{
}

void Ball::move(qreal delta)
{
    m_position.setX(m_position.x() + m_velocity.x() * delta);
    m_position.setY(m_position.y() + m_velocity.y() * delta);
}

void Ball::setVelocity(qreal vx, qreal vy)
{
    m_velocity = QPointF(vx, vy);
}

void Ball::checkBoundaryCollision(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    if (m_position.x() - m_radius <= minX) {
        m_position.setX(minX + m_radius);
        reverseX();
    }
    
    if (m_position.x() + m_radius >= maxX) {
        m_position.setX(maxX - m_radius);
        reverseX();
    }
    
    if (m_position.y() - m_radius <= minY) {
        m_position.setY(minY + m_radius);
        reverseY();
    }
}
