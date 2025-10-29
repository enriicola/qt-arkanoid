#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QPointF>
#include <QTimer>
#include <QElapsedTimer>
#include <QSet>
#include <vector>
#include <memory>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "PowerUp.h"
#include "SoundManager.h"

enum class GameState {
    Menu,
    Playing,
    Paused,
    GameOver,
    Victory
};

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(QWidget *parent = nullptr);

    QPointF screenToGame(const QPoint &screenPos) const;
    QPoint gameToScreen(const QPointF &gamePos) const;
    
    void togglePause();
    bool isPaused() const { return m_paused; }
    void startNewGame();
    void restartGame();
    GameState gameState() const { return m_gameState; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void gameLoop();

private:
    void drawBackground(QPainter &painter);
    void drawPaddle(QPainter &painter);
    void drawBall(QPainter &painter);
    void drawBricks(QPainter &painter);
    void drawScore(QPainter &painter);
    void drawFPS(QPainter &painter);
    void drawPauseOverlay(QPainter &painter);
    void drawGameOverOverlay(QPainter &painter);
    void drawVictoryOverlay(QPainter &painter);
    void drawHUD(QPainter &painter);
    void drawPowerUps(QPainter &painter);
    void drawActivePowerUps(QPainter &painter);
    
    void updateGame(qreal delta);
    void checkBallPaddleCollision();
    void checkBallBrickCollisions();
    void checkPowerUpCollisions();
    void checkGameState();
    void createBricks();
    void resetBall();
    void loseLife();
    void applyPowerUp(PowerUpType type);
    void spawnPowerUp(qreal x, qreal y);

private:
    static constexpr qreal GAME_WIDTH = 800.0;
    static constexpr qreal GAME_HEIGHT = 600.0;
    static constexpr int TARGET_FPS = 60;
    static constexpr qreal FRAME_TIME = 1000.0 / TARGET_FPS;
    static constexpr int STARTING_LIVES = 3;
    static constexpr qreal INVULNERABILITY_TIME = 2.0;
    
    std::unique_ptr<Paddle> m_paddle;
    std::unique_ptr<Ball> m_ball;
    std::vector<std::unique_ptr<Brick>> m_bricks;
    std::vector<std::unique_ptr<PowerUp>> m_powerUps;
    std::unique_ptr<SoundManager> m_soundManager;
    
    QTimer m_gameTimer;
    QElapsedTimer m_elapsedTimer;
    QElapsedTimer m_fpsTimer;
    QSet<int> m_pressedKeys;
    
    int m_score;
    bool m_paused;
    int m_frameCount;
    qreal m_fps;
    GameState m_gameState;
    int m_lives;
    int m_level;
    bool m_invulnerable;
    qreal m_invulnerabilityTimer;
    
    qreal m_paddleSizeTimer;
    qreal m_ballSpeedTimer;
    QString m_activePowerUpText;
    qreal m_powerUpTextTimer;
};

#endif
