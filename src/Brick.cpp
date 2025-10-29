#include "Brick.h"

Brick::Brick(qreal x, qreal y, qreal width, qreal height, const QColor &color, int hitPoints)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_color(color), 
      m_active(true), m_hitPoints(hitPoints), m_maxHitPoints(hitPoints)
{
}

QRectF Brick::rect() const
{
    return QRectF(m_x, m_y, m_width, m_height);
}

bool Brick::hit()
{
    if (!m_active) return false;
    
    m_hitPoints--;
    if (m_hitPoints <= 0) {
        m_active = false;
        return true;  // Brick destroyed
    }
    return false;  // Brick damaged but still active
}

QColor Brick::currentColor() const
{
    if (m_hitPoints <= 0 || !m_active) {
        return m_color;
    }
    
    // Darken color based on damage
    qreal ratio = static_cast<qreal>(m_hitPoints) / m_maxHitPoints;
    int r = static_cast<int>(m_color.red() * ratio);
    int g = static_cast<int>(m_color.green() * ratio);
    int b = static_cast<int>(m_color.blue() * ratio);
    
    return QColor(r, g, b);
}
