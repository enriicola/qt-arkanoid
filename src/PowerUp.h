#ifndef POWERUP_H
#define POWERUP_H

#include <QPointF>
#include <QRectF>
#include <QColor>
#include <QString>

enum class PowerUpType {
    BiggerPaddle,
    SmallerPaddle,
    SlowBall,
    FastBall,
    ExtraLife
};

class PowerUp
{
public:
    PowerUp(qreal x, qreal y, PowerUpType type);

    void move(qreal delta);
    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }
    
    QRectF rect() const;
    PowerUpType type() const { return m_type; }
    QColor color() const { return m_color; }
    QString name() const;

private:
    QPointF m_position;
    qreal m_width;
    qreal m_height;
    qreal m_speed;
    PowerUpType m_type;
    QColor m_color;
    bool m_active;
};

#endif
