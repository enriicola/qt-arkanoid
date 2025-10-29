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

void Ball::setSpeed(qreal speed)
{
    // Maintain current direction but change magnitude
    qreal currentSpeed = std::sqrt(m_velocity.x() * m_velocity.x() + 
                                   m_velocity.y() * m_velocity.y());
    
    if (currentSpeed > 0.0) {
        qreal scale = speed / currentSpeed;
        m_velocity.setX(m_velocity.x() * scale);
        m_velocity.setY(m_velocity.y() * scale);
    } else {
        // Default direction if velocity is zero
        m_velocity = QPointF(speed * 0.707, -speed * 0.707);
    }
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
