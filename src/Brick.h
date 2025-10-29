#ifndef BRICK_H
#define BRICK_H

#include <QRectF>
#include <QColor>

class Brick
{
public:
    Brick(qreal x, qreal y, qreal width, qreal height, const QColor &color);

    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }
    void destroy() { m_active = false; }

    QRectF rect() const;
    QColor color() const { return m_color; }

private:
    qreal m_x;
    qreal m_y;
    qreal m_width;
    qreal m_height;
    QColor m_color;
    bool m_active;
};

#endif
