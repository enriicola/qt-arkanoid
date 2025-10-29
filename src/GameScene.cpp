#include "GameScene.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <cmath>

GameScene::GameScene(QWidget *parent)
    : QWidget(parent), m_score(0), m_paused(false), m_frameCount(0), m_fps(0.0), m_gameState(GameState::Playing)
{
    setMinimumSize(800, 600);
    setFocusPolicy(Qt::StrongFocus);
    
    m_paddle = std::make_unique<Paddle>(350.0, 550.0, 100.0, 15.0);
    m_ball = std::make_unique<Ball>(400.0, 300.0, 8.0);
    
    createBricks();
    
    connect(&m_gameTimer, &QTimer::timeout, this, &GameScene::gameLoop);
    m_gameTimer.start(static_cast<int>(FRAME_TIME));
    m_elapsedTimer.start();
    m_fpsTimer.start();
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
    drawBricks(painter);
    drawPaddle(painter);
    drawBall(painter);
    drawScore(painter);
    drawFPS(painter);
    
    if (m_paused) {
        drawPauseOverlay(painter);
    } else if (m_gameState == GameState::GameOver) {
        drawGameOverOverlay(painter);
    } else if (m_gameState == GameState::Victory) {
        drawVictoryOverlay(painter);
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_P || event->key() == Qt::Key_Space) {
        if (m_gameState == GameState::Playing) {
            togglePause();
        }
    }
    
    if (event->key() == Qt::Key_R) {
        if (m_gameState == GameState::GameOver || m_gameState == GameState::Victory) {
            restartGame();
        }
    }
    
    m_pressedKeys.insert(event->key());
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    m_pressedKeys.remove(event->key());
}

void GameScene::gameLoop()
{
    qreal delta = m_elapsedTimer.elapsed() / 1000.0;
    m_elapsedTimer.restart();
    
    m_frameCount++;
    if (m_fpsTimer.elapsed() >= 1000) {
        m_fps = m_frameCount * 1000.0 / m_fpsTimer.elapsed();
        m_frameCount = 0;
        m_fpsTimer.restart();
    }
    
    if (!m_paused && m_gameState == GameState::Playing) {
        updateGame(delta);
        checkGameState();
    }
    update();
}

void GameScene::togglePause()
{
    m_paused = !m_paused;
}

void GameScene::startNewGame()
{
    restartGame();
}

void GameScene::restartGame()
{
    m_score = 0;
    m_paused = false;
    m_gameState = GameState::Playing;
    
    m_paddle->setPosition(350.0, 550.0);
    resetBall();
    
    m_bricks.clear();
    createBricks();
}

void GameScene::resetBall()
{
    m_ball->setVelocity(200.0, -200.0);
    m_paddle->setPosition(m_paddle->position().x(), 550.0);
}

void GameScene::updateGame(qreal delta)
{
    if (m_pressedKeys.contains(Qt::Key_A) || m_pressedKeys.contains(Qt::Key_Left)) {
        m_paddle->moveLeft(delta);
    }
    if (m_pressedKeys.contains(Qt::Key_D) || m_pressedKeys.contains(Qt::Key_Right)) {
        m_paddle->moveRight(delta);
    }
    
    m_paddle->constrainToBounds(0, GAME_WIDTH);
    
    m_ball->move(delta);
    m_ball->checkBoundaryCollision(0, GAME_WIDTH, 0, GAME_HEIGHT);
    
    checkBallPaddleCollision();
    checkBallBrickCollisions();
}

void GameScene::checkGameState()
{
    if (m_ball->y() > GAME_HEIGHT) {
        m_gameState = GameState::GameOver;
    }
    
    bool allBricksDestroyed = true;
    for (const auto &brick : m_bricks) {
        if (brick->isActive()) {
            allBricksDestroyed = false;
            break;
        }
    }
    
    if (allBricksDestroyed) {
        m_gameState = GameState::Victory;
    }
}

void GameScene::checkBallPaddleCollision()
{
    QRectF paddleRect = m_paddle->rect();
    QPointF ballPos = m_ball->position();
    qreal ballRadius = m_ball->radius();
    
    if (ballPos.y() + ballRadius >= paddleRect.top() &&
        ballPos.y() - ballRadius <= paddleRect.bottom() &&
        ballPos.x() + ballRadius >= paddleRect.left() &&
        ballPos.x() - ballRadius <= paddleRect.right()) {
        
        qreal hitPos = (ballPos.x() - paddleRect.left()) / paddleRect.width();
        hitPos = qBound(0.0, hitPos, 1.0);
        
        qreal angle = (hitPos - 0.5) * 2.0;
        qreal speed = std::sqrt(m_ball->velocity().x() * m_ball->velocity().x() + 
                               m_ball->velocity().y() * m_ball->velocity().y());
        
        qreal newVx = angle * speed * 0.8;
        qreal newVy = -std::abs(speed * 0.8);
        
        m_ball->setVelocity(newVx, newVy);
    }
}

void GameScene::checkBallBrickCollisions()
{
    QPointF ballPos = m_ball->position();
    qreal ballRadius = m_ball->radius();
    
    for (auto &brick : m_bricks) {
        if (!brick->isActive()) continue;
        
        QRectF brickRect = brick->rect();
        
        if (ballPos.x() + ballRadius >= brickRect.left() &&
            ballPos.x() - ballRadius <= brickRect.right() &&
            ballPos.y() + ballRadius >= brickRect.top() &&
            ballPos.y() - ballRadius <= brickRect.bottom()) {
            
            brick->destroy();
            m_score += 10;
            
            qreal brickCenterX = brickRect.center().x();
            qreal brickCenterY = brickRect.center().y();
            
            qreal dx = ballPos.x() - brickCenterX;
            qreal dy = ballPos.y() - brickCenterY;
            
            if (std::abs(dx / brickRect.width()) > std::abs(dy / brickRect.height())) {
                m_ball->reverseX();
            } else {
                m_ball->reverseY();
            }
            
            break;
        }
    }
}

void GameScene::createBricks()
{
    const int rows = 5;
    const int cols = 10;
    const qreal brickWidth = 70.0;
    const qreal brickHeight = 25.0;
    const qreal padding = 5.0;
    const qreal offsetX = (GAME_WIDTH - (cols * (brickWidth + padding) - padding)) / 2.0;
    const qreal offsetY = 50.0;
    
    QColor colors[] = {
        QColor(255, 100, 100),
        QColor(255, 180, 100),
        QColor(255, 255, 100),
        QColor(100, 255, 100),
        QColor(100, 100, 255)
    };
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            qreal x = offsetX + col * (brickWidth + padding);
            qreal y = offsetY + row * (brickHeight + padding);
            m_bricks.push_back(std::make_unique<Brick>(x, y, brickWidth, brickHeight, colors[row]));
        }
    }
}

void GameScene::drawBackground(QPainter &painter)
{
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(20, 30, 48));
    gradient.setColorAt(1, QColor(36, 59, 85));
    
    painter.fillRect(rect(), gradient);
}

void GameScene::drawPaddle(QPainter &painter)
{
    QRectF paddleRect = m_paddle->rect();
    QPoint screenPos = gameToScreen(paddleRect.topLeft());
    QPoint screenBottomRight = gameToScreen(paddleRect.bottomRight());
    
    QRectF screenRect(screenPos, screenBottomRight);
    
    QLinearGradient gradient(screenRect.topLeft(), screenRect.bottomLeft());
    gradient.setColorAt(0, QColor(100, 200, 255));
    gradient.setColorAt(1, QColor(50, 150, 255));
    
    painter.setBrush(gradient);
    painter.setPen(QPen(QColor(200, 230, 255), 2));
    painter.drawRoundedRect(screenRect, 5, 5);
}

void GameScene::drawBall(QPainter &painter)
{
    QPoint screenPos = gameToScreen(m_ball->position());
    qreal screenRadius = m_ball->radius() * (width() / GAME_WIDTH);
    
    QRadialGradient gradient(screenPos, screenRadius);
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, QColor(200, 200, 255));
    
    painter.setBrush(gradient);
    painter.setPen(QPen(QColor(150, 150, 255), 2));
    painter.drawEllipse(screenPos, static_cast<int>(screenRadius), static_cast<int>(screenRadius));
}

void GameScene::drawBricks(QPainter &painter)
{
    for (const auto &brick : m_bricks) {
        if (!brick->isActive()) continue;
        
        QRectF brickRect = brick->rect();
        QPoint screenPos = gameToScreen(brickRect.topLeft());
        QPoint screenBottomRight = gameToScreen(brickRect.bottomRight());
        QRectF screenRect(screenPos, screenBottomRight);
        
        QLinearGradient gradient(screenRect.topLeft(), screenRect.bottomLeft());
        QColor color = brick->color();
        gradient.setColorAt(0, color.lighter(120));
        gradient.setColorAt(1, color);
        
        painter.setBrush(gradient);
        painter.setPen(QPen(color.darker(150), 2));
        painter.drawRoundedRect(screenRect, 3, 3);
    }
}

void GameScene::drawScore(QPainter &painter)
{
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(10, 25, QString("Score: %1").arg(m_score));
    
    int activeBricks = 0;
    for (const auto &brick : m_bricks) {
        if (brick->isActive()) activeBricks++;
    }
    painter.drawText(width() - 150, 25, QString("Bricks: %1").arg(activeBricks));
}

void GameScene::drawFPS(QPainter &painter)
{
    painter.setPen(QColor(200, 200, 200));
    painter.setFont(QFont("Arial", 10));
    painter.drawText(10, height() - 10, QString("FPS: %1").arg(m_fps, 0, 'f', 1));
}

void GameScene::drawPauseOverlay(QPainter &painter)
{
    painter.fillRect(rect(), QColor(0, 0, 0, 150));
    
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 48, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, "PAUSED");
    
    painter.setFont(QFont("Arial", 16));
    QRect textRect = rect();
    textRect.translate(0, 60);
    painter.drawText(textRect, Qt::AlignCenter, "Press P or Space to resume");
}

void GameScene::drawGameOverOverlay(QPainter &painter)
{
    painter.fillRect(rect(), QColor(0, 0, 0, 180));
    
    painter.setPen(QColor(255, 100, 100));
    painter.setFont(QFont("Arial", 48, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
    
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 20));
    QRect textRect = rect();
    textRect.translate(0, 60);
    painter.drawText(textRect, Qt::AlignCenter, QString("Final Score: %1").arg(m_score));
    
    painter.setFont(QFont("Arial", 16));
    textRect.translate(0, 40);
    painter.drawText(textRect, Qt::AlignCenter, "Press R to restart");
}

void GameScene::drawVictoryOverlay(QPainter &painter)
{
    painter.fillRect(rect(), QColor(0, 0, 0, 180));
    
    painter.setPen(QColor(100, 255, 100));
    painter.setFont(QFont("Arial", 48, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, "VICTORY!");
    
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 20));
    QRect textRect = rect();
    textRect.translate(0, 60);
    painter.drawText(textRect, Qt::AlignCenter, QString("Score: %1").arg(m_score));
    
    painter.setFont(QFont("Arial", 16));
    textRect.translate(0, 40);
    painter.drawText(textRect, Qt::AlignCenter, "Press R to play again");
}
