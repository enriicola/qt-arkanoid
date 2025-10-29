#include "Particle.h"
#include <algorithm>

Particle::Particle(qreal x, qreal y, qreal vx, qreal vy, const QColor &color, qreal lifetime)
    : m_position(x, y), m_velocity(vx, vy), m_baseColor(color),
      m_lifetime(lifetime), m_maxLifetime(lifetime), m_gravity(500.0)
{
}

void Particle::update(qreal delta)
{
    m_lifetime -= delta;
    
    if (m_lifetime > 0.0) {
        m_position += m_velocity * delta;
        m_velocity.setY(m_velocity.y() + m_gravity * delta);
    }
}

QColor Particle::color() const
{
    QColor c = m_baseColor;
    c.setAlphaF(alpha());
    return c;
}

qreal Particle::size() const
{
    qreal ratio = m_lifetime / m_maxLifetime;
    return 4.0 * ratio + 1.0;
}

qreal Particle::alpha() const
{
    return std::max(0.0, m_lifetime / m_maxLifetime);
}
