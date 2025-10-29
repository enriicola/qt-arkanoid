#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

class QAction;

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

private slots:
    void onNewGame();
    void onPause();

private:
    QAction *newGameAction;
    QAction *pauseAction;
    QAction *exitAction;
    QAction *aboutQtAction;
};

#endif
