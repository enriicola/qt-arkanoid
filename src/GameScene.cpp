#include "GameScene.h"
#include <QPainter>
#include <QPaintEvent>

GameScene::GameScene(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800, 600);
}

void GameScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    drawBackground(painter);
    drawGrid(painter);
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
    
    painter.setPen(QPen(QColor(100, 200, 255, 80), 2));
    painter.drawRect(rect().adjusted(5, 5, -5, -5));
    
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(20, 30, "Game Scene - Ready to play!");
}
