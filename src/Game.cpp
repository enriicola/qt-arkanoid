#include "Game.h"
#include <QScreen>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QMessageBox>

Game::Game(QWidget *parent)
    : QMainWindow(parent)
{
    setupWindow();
    centerWindow();
    createActions();
    createMenus();
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
    gameMenu->addAction(exitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutQtAction);
}

void Game::onNewGame()
{
    QMessageBox::information(this, tr("New Game"), 
                            tr("New Game functionality will be implemented later."));
}

void Game::onPause()
{
    QMessageBox::information(this, tr("Pause"), 
                            tr("Pause functionality will be implemented later."));
}
