#include "Brick.h"

Brick::Brick(qreal x, qreal y, qreal width, qreal height, const QColor &color)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_color(color), m_active(true)
{
}

QRectF Brick::rect() const
{
    return QRectF(m_x, m_y, m_width, m_height);
}
