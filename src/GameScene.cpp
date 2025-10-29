#include "GameScene.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "PowerUp.h"
#include "SoundManager.h"
#include "Particle.h"
#include "HighScoreManager.h"
#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QInputDialog>
#include <cmath>
#include <cstdlib>
#include <ctime>

GameScene::GameScene(QWidget *parent)
    : QWidget(parent), m_score(0), m_paused(false), m_frameCount(0), m_fps(0.0), 
      m_gameState(GameState::Playing), m_lives(STARTING_LIVES), m_level(1),
      m_invulnerable(false), m_invulnerabilityTimer(0.0),
      m_paddleSizeTimer(0.0), m_ballSpeedTimer(0.0), m_powerUpTextTimer(0.0),
      m_screenShakeAmount(0.0), m_screenShakeDuration(0.0),
      m_highScoreManager(nullptr)
{
    setMinimumSize(800, 600);
    setFocusPolicy(Qt::StrongFocus);
    
    std::srand(std::time(nullptr));
    
    m_paddle = std::make_unique<Paddle>(350.0, 550.0, 100.0, 15.0);
    m_ball = std::make_unique<Ball>(400.0, 300.0, 8.0);
    m_soundManager = std::make_unique<SoundManager>(this);
    
    createBricks();
    
    connect(&m_gameTimer, &QTimer::timeout, this, &GameScene::gameLoop);
    m_gameTimer.start(static_cast<int>(FRAME_TIME));
    m_elapsedTimer.start();
    m_fpsTimer.start();
    
    m_soundManager->playBackgroundMusic();
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
    
    // Apply screen shake
    if (m_screenShakeDuration > 0.0) {
        painter.translate(m_screenShakeOffset);
    }
    
    drawBackground(painter);
    drawBallTrail(painter);
    drawParticles(painter);
    drawBricks(painter);
    drawPaddle(painter);
    drawBall(painter);
    drawPowerUps(painter);
    drawHUD(painter);
    drawActivePowerUps(painter);
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
    m_lives = STARTING_LIVES;
    m_level = 1;
    m_invulnerable = false;
    m_invulnerabilityTimer = 0.0;
    m_paddleSizeTimer = 0.0;
    m_ballSpeedTimer = 0.0;
    m_powerUpTextTimer = 0.0;
    
    m_paddle->setPosition(350.0, 550.0);
    m_paddle->setWidth(100.0);
    resetBall();
    
    m_bricks.clear();
    createBricks();
    
    m_powerUps.clear();
    m_particles.clear();
    m_ballTrail.clear();
    m_screenShakeAmount = 0.0;
    m_screenShakeDuration = 0.0;
    m_screenShakeOffset = QPointF(0, 0);
}

void GameScene::resetBall()
{
    m_ball = std::make_unique<Ball>(400.0, 300.0, 8.0);
    m_ball->setVelocity(200.0, -200.0);
}

void GameScene::loseLife()
{
    m_lives--;
    m_soundManager->playSound(SoundManager::Sound::LoseLife);
    
    // Big screen shake on life loss
    m_screenShakeAmount = 8.0;
    m_screenShakeDuration = 0.3;
    
    if (m_lives <= 0) {
        m_gameState = GameState::GameOver;
        m_soundManager->playSound(SoundManager::Sound::GameOver);
        checkForHighScore();
    } else {
        m_paddle->setPosition(350.0, 550.0);
        resetBall();
        m_invulnerable = true;
        m_invulnerabilityTimer = INVULNERABILITY_TIME;
    }
}

void GameScene::updateGame(qreal delta)
{
    if (m_invulnerable) {
        m_invulnerabilityTimer -= delta;
        if (m_invulnerabilityTimer <= 0.0) {
            m_invulnerable = false;
            m_invulnerabilityTimer = 0.0;
        }
    }
    
    if (m_paddleSizeTimer > 0.0) {
        m_paddleSizeTimer -= delta;
        if (m_paddleSizeTimer <= 0.0) {
            m_paddle->setWidth(100.0);
            m_paddleSizeTimer = 0.0;
        }
    }
    
    if (m_ballSpeedTimer > 0.0) {
        m_ballSpeedTimer -= delta;
        if (m_ballSpeedTimer <= 0.0) {
            QPointF vel = m_ball->velocity();
            qreal currentSpeed = std::sqrt(vel.x() * vel.x() + vel.y() * vel.y());
            qreal normalSpeed = 300.0;
            if (currentSpeed > 0.0) {
                qreal scale = normalSpeed / currentSpeed;
                m_ball->setVelocity(vel.x() * scale, vel.y() * scale);
            }
            m_ballSpeedTimer = 0.0;
        }
    }
    
    if (m_powerUpTextTimer > 0.0) {
        m_powerUpTextTimer -= delta;
    }
    
    updateScreenShake(delta);
    
    // Update particles
    for (auto &particle : m_particles) {
        particle.update(delta);
    }
    m_particles.erase(
        std::remove_if(m_particles.begin(), m_particles.end(),
            [](const Particle &p) { return !p.isAlive(); }),
        m_particles.end()
    );
    
    // Update ball trail
    m_ballTrail.push_back(m_ball->position());
    if (m_ballTrail.size() > 10) {
        m_ballTrail.erase(m_ballTrail.begin());
    }
    
    if (m_pressedKeys.contains(Qt::Key_A) || m_pressedKeys.contains(Qt::Key_Left)) {
        m_paddle->moveLeft(delta);
    }
    if (m_pressedKeys.contains(Qt::Key_D) || m_pressedKeys.contains(Qt::Key_Right)) {
        m_paddle->moveRight(delta);
    }
    
    m_paddle->constrainToBounds(0, GAME_WIDTH);
    
    m_ball->move(delta);
    m_ball->checkBoundaryCollision(0, GAME_WIDTH, 0, GAME_HEIGHT);
    
    for (auto &powerUp : m_powerUps) {
        if (powerUp->isActive()) {
            powerUp->move(delta);
            if (powerUp->rect().top() > GAME_HEIGHT) {
                powerUp->setActive(false);
            }
        }
    }
    
    if (!m_invulnerable) {
        checkBallPaddleCollision();
    }
    checkBallBrickCollisions();
    checkPowerUpCollisions();
}

void GameScene::checkGameState()
{
    if (m_ball->y() > GAME_HEIGHT) {
        loseLife();
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
        m_soundManager->playSound(SoundManager::Sound::Victory);
        checkForHighScore();
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
        m_soundManager->playSound(SoundManager::Sound::BallHit);
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
            m_soundManager->playSound(SoundManager::Sound::BrickBreak);
            
            // Spawn particles for brick destruction
            spawnParticles(brickRect.center().x(), brickRect.center().y(), brick->color(), 15);
            
            // Add screen shake
            m_screenShakeAmount = 3.0;
            m_screenShakeDuration = 0.1;
            
            spawnPowerUp(brickRect.center().x(), brickRect.center().y());
            
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
    if (m_invulnerable && static_cast<int>(m_invulnerabilityTimer * 10) % 2 == 0) {
        return;
    }
    
    QRectF paddleRect = m_paddle->rect();
    QPoint screenPos = gameToScreen(paddleRect.topLeft());
    QPoint screenBottomRight = gameToScreen(paddleRect.bottomRight());
    
    QRectF screenRect(screenPos, screenBottomRight);
    
    QLinearGradient gradient(screenRect.topLeft(), screenRect.bottomLeft());
    
    if (m_invulnerable) {
        gradient.setColorAt(0, QColor(255, 200, 100));
        gradient.setColorAt(1, QColor(255, 150, 50));
    } else {
        gradient.setColorAt(0, QColor(100, 200, 255));
        gradient.setColorAt(1, QColor(50, 150, 255));
    }
    
    painter.setBrush(gradient);
    painter.setPen(QPen(m_invulnerable ? QColor(255, 230, 200) : QColor(200, 230, 255), 2));
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

void GameScene::drawHUD(QPainter &painter)
{
    QRect topPanel(0, 0, width(), 45);
    painter.fillRect(topPanel, QColor(0, 0, 0, 120));
    
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(15, 28, QString("Score: %1").arg(m_score));
    
    painter.drawText(width() / 2 - 50, 28, QString("Level: %1").arg(m_level));
    
    painter.setPen(QColor(255, 100, 100));
    QString livesText = QString("Lives: %1").arg(m_lives);
    painter.drawText(width() - 130, 28, livesText);
    
    int activeBricks = 0;
    for (const auto &brick : m_bricks) {
        if (brick->isActive()) activeBricks++;
    }
    
    painter.setPen(QColor(150, 200, 255));
    painter.setFont(QFont("Arial", 12));
    painter.drawText(15, height() - 35, QString("Bricks: %1").arg(activeBricks));
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

void GameScene::spawnPowerUp(qreal x, qreal y)
{
    if (std::rand() % 100 < 20) {
        PowerUpType type = static_cast<PowerUpType>(std::rand() % 5);
        m_powerUps.push_back(std::make_unique<PowerUp>(x, y, type));
    }
}

void GameScene::checkPowerUpCollisions()
{
    QRectF paddleRect = m_paddle->rect();
    
    for (auto &powerUp : m_powerUps) {
        if (!powerUp->isActive()) continue;
        
        QRectF powerUpRect = powerUp->rect();
        
        if (paddleRect.intersects(powerUpRect)) {
            // Spawn particles when power-up is collected
            spawnParticles(powerUpRect.center().x(), powerUpRect.center().y(), 
                          powerUp->color(), 10);
            applyPowerUp(powerUp->type());
            powerUp->setActive(false);
        }
    }
}

void GameScene::applyPowerUp(PowerUpType type)
{
    const qreal DURATION = 10.0;
    m_soundManager->playSound(SoundManager::Sound::PowerUp);
    
    switch (type) {
        case PowerUpType::BiggerPaddle:
            if (m_paddleSizeTimer <= 0.0) {
                m_paddle->setWidth(m_paddle->width() * 1.5);
            }
            m_paddleSizeTimer = DURATION;
            m_activePowerUpText = "Bigger Paddle!";
            m_powerUpTextTimer = 2.0;
            break;
            
        case PowerUpType::SmallerPaddle:
            if (m_paddleSizeTimer <= 0.0) {
                m_paddle->setWidth(m_paddle->width() * 0.6);
            }
            m_paddleSizeTimer = DURATION;
            m_activePowerUpText = "Smaller Paddle!";
            m_powerUpTextTimer = 2.0;
            break;
            
        case PowerUpType::SlowBall:
            if (m_ballSpeedTimer <= 0.0) {
                QPointF vel = m_ball->velocity();
                m_ball->setVelocity(vel.x() * 0.7, vel.y() * 0.7);
            }
            m_ballSpeedTimer = DURATION;
            m_activePowerUpText = "Slow Ball!";
            m_powerUpTextTimer = 2.0;
            break;
            
        case PowerUpType::FastBall:
            if (m_ballSpeedTimer <= 0.0) {
                QPointF vel = m_ball->velocity();
                m_ball->setVelocity(vel.x() * 1.5, vel.y() * 1.5);
            }
            m_ballSpeedTimer = DURATION;
            m_activePowerUpText = "Fast Ball!";
            m_powerUpTextTimer = 2.0;
            break;
            
        case PowerUpType::ExtraLife:
            m_lives++;
            m_activePowerUpText = "Extra Life!";
            m_powerUpTextTimer = 2.0;
            break;
    }
}

void GameScene::drawPowerUps(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    
    for (const auto &powerUp : m_powerUps) {
        if (!powerUp->isActive()) continue;
        
        QRectF powerUpRect = powerUp->rect();
        QPoint screenPos = gameToScreen(powerUpRect.topLeft());
        QPoint screenBottomRight = gameToScreen(powerUpRect.bottomRight());
        QRectF screenRect(screenPos, screenBottomRight);
        
        QLinearGradient gradient(screenRect.topLeft(), screenRect.bottomLeft());
        QColor color = powerUp->color();
        gradient.setColorAt(0, color.lighter(130));
        gradient.setColorAt(1, color);
        
        painter.setBrush(gradient);
        painter.setPen(QPen(color.darker(150), 2));
        painter.drawRoundedRect(screenRect, 4, 4);
        
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 8, QFont::Bold));
        painter.drawText(screenRect, Qt::AlignCenter, powerUp->name().at(0));
    }
}

void GameScene::drawActivePowerUps(QPainter &painter)
{
    if (m_powerUpTextTimer > 0.0) {
        painter.setPen(QColor(255, 255, 100));
        painter.setFont(QFont("Arial", 20, QFont::Bold));
        
        QRect textRect = rect();
        textRect.setTop(height() / 2 - 50);
        textRect.setHeight(50);
        
        painter.drawText(textRect, Qt::AlignCenter, m_activePowerUpText);
    }
}

void GameScene::drawParticles(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    
    for (const auto &particle : m_particles) {
        if (!particle.isAlive()) continue;
        
        QPoint screenPos = gameToScreen(particle.position());
        qreal size = particle.size();
        QColor color = particle.color();
        
        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(screenPos, static_cast<int>(size), static_cast<int>(size));
    }
}

void GameScene::drawBallTrail(QPainter &painter)
{
    if (m_ballTrail.size() < 2) return;
    
    painter.setRenderHint(QPainter::Antialiasing);
    
    for (size_t i = 0; i < m_ballTrail.size(); ++i) {
        qreal alpha = static_cast<qreal>(i) / m_ballTrail.size();
        qreal radius = m_ball->radius() * alpha * 0.5;
        
        QPoint screenPos = gameToScreen(m_ballTrail[i]);
        
        QColor trailColor(150, 200, 255, static_cast<int>(alpha * 100));
        painter.setBrush(trailColor);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(screenPos, static_cast<int>(radius), static_cast<int>(radius));
    }
}

void GameScene::spawnParticles(qreal x, qreal y, const QColor &color, int count)
{
    for (int i = 0; i < count; ++i) {
        qreal angle = (std::rand() % 360) * M_PI / 180.0;
        qreal speed = 100.0 + (std::rand() % 200);
        qreal vx = std::cos(angle) * speed;
        qreal vy = std::sin(angle) * speed - 100.0;
        qreal lifetime = 0.5 + (std::rand() % 100) / 100.0;
        
        m_particles.emplace_back(x, y, vx, vy, color, lifetime);
    }
}

void GameScene::updateScreenShake(qreal delta)
{
    if (m_screenShakeDuration > 0.0) {
        m_screenShakeDuration -= delta;
        
        if (m_screenShakeDuration > 0.0) {
            qreal angle = (std::rand() % 360) * M_PI / 180.0;
            m_screenShakeOffset.setX(std::cos(angle) * m_screenShakeAmount);
            m_screenShakeOffset.setY(std::sin(angle) * m_screenShakeAmount);
        } else {
            m_screenShakeOffset = QPointF(0, 0);
            m_screenShakeDuration = 0.0;
        }
    }
}

void GameScene::setHighScoreManager(HighScoreManager *manager)
{
    m_highScoreManager = manager;
}

void GameScene::applySoundSettings(bool soundEnabled, bool musicEnabled, 
                                   float soundVolume, float musicVolume)
{
    if (m_soundManager) {
        m_soundManager->setSoundEnabled(soundEnabled);
        m_soundManager->setMusicEnabled(musicEnabled);
        m_soundManager->setSoundVolume(soundVolume);
        m_soundManager->setMusicVolume(musicVolume);
    }
}

void GameScene::checkForHighScore()
{
    if (!m_highScoreManager) return;
    
    if (m_highScoreManager->isHighScore(m_score)) {
        bool ok;
        QString name = QInputDialog::getText(
            this,
            "High Score!",
            QString("Congratulations! You achieved a high score of %1!\nEnter your name:").arg(m_score),
            QLineEdit::Normal,
            "Player",
            &ok
        );
        
        if (ok && !name.isEmpty()) {
            m_highScoreManager->addHighScore(name, m_score);
        }
    }
}
