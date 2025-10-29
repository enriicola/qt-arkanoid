#include "Game.h"
#include "GameScene.h"
#include "SettingsDialog.h"
#include "HighScoreManager.h"
#include "HighScoreDialog.h"
#include "LevelManager.h"
#include <QScreen>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>

Game::Game(QWidget *parent)
    : QMainWindow(parent), settingsDialog(nullptr)
{
    setupWindow();
    centerWindow();
    
    highScoreManager = new HighScoreManager(this);
    levelManager = new LevelManager(this);
    levelManager->createDefaultLevels();
    
    createActions();
    createMenus();
    
    gameScene = new GameScene(this);
    gameScene->setHighScoreManager(highScoreManager);
    gameScene->setLevelManager(levelManager);
    gameScene->loadCurrentLevel();
    setCentralWidget(gameScene);
    
    applySettings();
}

Game::~Game()
{
}

void Game::setupWindow()
{
    setFixedSize(800, 600);
    setWindowTitle("Qt Arkanoid");
}

void Game::centerWindow()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }
}

void Game::createActions()
{
    newGameAction = new QAction(tr("&New Game"), this);
    newGameAction->setShortcut(tr("Ctrl+N"));
    connect(newGameAction, &QAction::triggered, this, &Game::onNewGame);

    pauseAction = new QAction(tr("&Pause"), this);
    pauseAction->setShortcut(tr("Ctrl+P"));
    connect(pauseAction, &QAction::triggered, this, &Game::onPause);
    
    settingsAction = new QAction(tr("&Settings"), this);
    settingsAction->setShortcut(tr("Ctrl+S"));
    connect(settingsAction, &QAction::triggered, this, &Game::onSettings);
    
    highScoresAction = new QAction(tr("&High Scores"), this);
    highScoresAction->setShortcut(tr("Ctrl+H"));
    connect(highScoresAction, &QAction::triggered, this, &Game::onHighScores);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void Game::createMenus()
{
    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(newGameAction);
    gameMenu->addAction(pauseAction);
    gameMenu->addSeparator();
    gameMenu->addAction(highScoresAction);
    gameMenu->addAction(settingsAction);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutQtAction);
}

void Game::onNewGame()
{
    if (gameScene) {
        gameScene->startNewGame();
    }
}

void Game::onPause()
{
    if (gameScene) {
        gameScene->togglePause();
    }
}

void Game::onSettings()
{
    if (!settingsDialog) {
        settingsDialog = new SettingsDialog(this);
        connect(settingsDialog, &SettingsDialog::settingsChanged,
                this, &Game::onSettingsChanged);
    }
    settingsDialog->exec();
}

void Game::onHighScores()
{
    HighScoreDialog dialog(highScoreManager, this);
    dialog.exec();
}

void Game::onSettingsChanged()
{
    applySettings();
}

void Game::applySettings()
{
    if (!settingsDialog) {
        settingsDialog = new SettingsDialog(this);
        connect(settingsDialog, &SettingsDialog::settingsChanged,
                this, &Game::onSettingsChanged);
    }
    
    if (gameScene) {
        gameScene->applySoundSettings(
            settingsDialog->isSoundEnabled(),
            settingsDialog->isMusicEnabled(),
            settingsDialog->soundVolume() / 100.0f,
            settingsDialog->musicVolume() / 100.0f
        );
    }
}
