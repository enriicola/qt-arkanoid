#ifndef PARTICLE_H
#define PARTICLE_H

#include <QPointF>
#include <QColor>

class Particle
{
public:
    Particle(qreal x, qreal y, qreal vx, qreal vy, const QColor &color, qreal lifetime);
    
    void update(qreal delta);
    bool isAlive() const { return m_lifetime > 0.0; }
    
    QPointF position() const { return m_position; }
    QColor color() const;
    qreal size() const;
    qreal alpha() const;

private:
    QPointF m_position;
    QPointF m_velocity;
    QColor m_baseColor;
    qreal m_lifetime;
    qreal m_maxLifetime;
    qreal m_gravity;
};

#endif
