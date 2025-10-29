#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QPointF>

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(QWidget *parent = nullptr);

    QPointF screenToGame(const QPoint &screenPos) const;
    QPoint gameToScreen(const QPointF &gamePos) const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void drawBackground(QPainter &painter);
    void drawGrid(QPainter &painter);
    void drawCoordinateSystem(QPainter &painter);
    void drawBoundaries(QPainter &painter);
    void drawMousePosition(QPainter &painter);

private:
    static constexpr qreal GAME_WIDTH = 800.0;
    static constexpr qreal GAME_HEIGHT = 600.0;
    QPointF lastMousePos;
    bool mouseClicked;
};

#endif
