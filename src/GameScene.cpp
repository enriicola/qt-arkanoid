#include "GameScene.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

GameScene::GameScene(QWidget *parent)
    : QWidget(parent), mouseClicked(false)
{
    setMinimumSize(800, 600);
    setMouseTracking(true);
}

QPointF GameScene::screenToGame(const QPoint &screenPos) const
{
    qreal scaleX = GAME_WIDTH / width();
    qreal scaleY = GAME_HEIGHT / height();
    
    return QPointF(screenPos.x() * scaleX, screenPos.y() * scaleY);
}

QPoint GameScene::gameToScreen(const QPointF &gamePos) const
{
    qreal scaleX = width() / GAME_WIDTH;
    qreal scaleY = height() / GAME_HEIGHT;
    
    return QPoint(static_cast<int>(gamePos.x() * scaleX), 
                  static_cast<int>(gamePos.y() * scaleY));
}

void GameScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    drawBackground(painter);
    drawGrid(painter);
    drawCoordinateSystem(painter);
    drawBoundaries(painter);
    drawMousePosition(painter);
}

void GameScene::mousePressEvent(QMouseEvent *event)
{
    lastMousePos = screenToGame(event->pos());
    mouseClicked = true;
    update();
}

void GameScene::drawBackground(QPainter &painter)
{
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(20, 30, 48));
    gradient.setColorAt(1, QColor(36, 59, 85));
    
    painter.fillRect(rect(), gradient);
}

void GameScene::drawGrid(QPainter &painter)
{
    painter.setPen(QPen(QColor(255, 255, 255, 30), 1));
    
    int gridSize = 50;
    
    for (int x = 0; x < width(); x += gridSize) {
        painter.drawLine(x, 0, x, height());
    }
    
    for (int y = 0; y < height(); y += gridSize) {
        painter.drawLine(0, y, width(), y);
    }
}

void GameScene::drawCoordinateSystem(QPainter &painter)
{
    painter.setPen(QPen(QColor(255, 100, 100), 2));
    painter.drawLine(10, 10, 60, 10);
    painter.drawText(65, 15, "X");
    
    painter.setPen(QPen(QColor(100, 255, 100), 2));
    painter.drawLine(10, 10, 10, 60);
    painter.drawText(5, 75, "Y");
    
    painter.setPen(QPen(QColor(255, 255, 100), 2));
    painter.drawEllipse(QPoint(10, 10), 3, 3);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(15, 25, "Origin (0,0)");
}

void GameScene::drawBoundaries(QPainter &painter)
{
    painter.setPen(QPen(QColor(100, 200, 255, 120), 3));
    painter.drawRect(rect().adjusted(2, 2, -2, -2));
    
    painter.setFont(QFont("Arial", 10));
    painter.setPen(QColor(100, 200, 255, 200));
    painter.drawText(width() - 150, 20, 
                    QString("Game: %1x%2")
                    .arg(GAME_WIDTH)
                    .arg(GAME_HEIGHT));
    painter.drawText(width() - 150, 35, 
                    QString("Screen: %1x%2")
                    .arg(width())
                    .arg(height()));
}

void GameScene::drawMousePosition(QPainter &painter)
{
    if (mouseClicked) {
        painter.setPen(QPen(Qt::cyan, 2));
        painter.setFont(QFont("Arial", 11, QFont::Bold));
        
        QString text = QString("Last Click - Game: (%1, %2)")
                      .arg(lastMousePos.x(), 0, 'f', 1)
                      .arg(lastMousePos.y(), 0, 'f', 1);
        
        painter.drawText(20, height() - 20, text);
        
        QPoint screenPos = gameToScreen(lastMousePos);
        painter.drawEllipse(screenPos, 5, 5);
        painter.drawLine(screenPos.x() - 10, screenPos.y(), 
                        screenPos.x() + 10, screenPos.y());
        painter.drawLine(screenPos.x(), screenPos.y() - 10, 
                        screenPos.x(), screenPos.y() + 10);
    } else {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 10));
        painter.drawText(20, height() - 20, "Click anywhere to test coordinate system!");
    }
}
