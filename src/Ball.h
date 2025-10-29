#ifndef BALL_H
#define BALL_H

#include <QPointF>

class Ball
{
public:
    Ball(qreal x, qreal y, qreal radius);

    void move(qreal delta);
    void setVelocity(qreal vx, qreal vy);
    void reverseX() { m_velocity.setX(-m_velocity.x()); }
    void reverseY() { m_velocity.setY(-m_velocity.y()); }
    void checkBoundaryCollision(qreal minX, qreal maxX, qreal minY, qreal maxY);

    QPointF position() const { return m_position; }
    QPointF velocity() const { return m_velocity; }
    qreal radius() const { return m_radius; }
    qreal x() const { return m_position.x(); }
    qreal y() const { return m_position.y(); }

private:
    QPointF m_position;
    QPointF m_velocity;
    qreal m_radius;
};

#endif
