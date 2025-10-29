#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

class QAction;
class GameScene;
class SettingsDialog;
class HighScoreManager;

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private:
    void setupWindow();
    void centerWindow();
    void createMenus();
    void createActions();
    void applySettings();

private slots:
    void onNewGame();
    void onPause();
    void onSettings();
    void onHighScores();
    void onSettingsChanged();

private:
    QAction *newGameAction;
    QAction *pauseAction;
    QAction *settingsAction;
    QAction *highScoresAction;
    QAction *exitAction;
    QAction *aboutQtAction;
    GameScene *gameScene;
    SettingsDialog *settingsDialog;
    HighScoreManager *highScoreManager;
};

#endif
