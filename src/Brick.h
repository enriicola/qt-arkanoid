#ifndef BRICK_H
#define BRICK_H

#include <QRectF>
#include <QColor>

class Brick
{
public:
    Brick(qreal x, qreal y, qreal width, qreal height, const QColor &color, int hitPoints = 1);

    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }
    void destroy() { m_active = false; }
    bool hit();  // Returns true if brick is destroyed

    QRectF rect() const;
    QColor color() const { return m_color; }
    QColor currentColor() const;  // Returns color based on hit points
    int hitPoints() const { return m_hitPoints; }
    int maxHitPoints() const { return m_maxHitPoints; }

private:
    qreal m_x;
    qreal m_y;
    qreal m_width;
    qreal m_height;
    QColor m_color;
    bool m_active;
    int m_hitPoints;
    int m_maxHitPoints;
};

#endif
