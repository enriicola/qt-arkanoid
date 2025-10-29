#ifndef PADDLE_H
#define PADDLE_H

#include <QPointF>
#include <QRectF>

class Paddle
{
public:
    Paddle(qreal x, qreal y, qreal width, qreal height);

    void moveLeft(qreal delta);
    void moveRight(qreal delta);
    void setPosition(qreal x, qreal y);
    void constrainToBounds(qreal minX, qreal maxX);

    QRectF rect() const;
    QPointF position() const { return m_position; }
    qreal width() const { return m_width; }
    qreal height() const { return m_height; }
    qreal speed() const { return m_speed; }

private:
    QPointF m_position;
    qreal m_width;
    qreal m_height;
    qreal m_speed;
};

#endif
