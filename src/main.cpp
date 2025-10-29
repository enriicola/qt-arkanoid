#include <QApplication>
#include "Game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Step 2 - Use custom Game class instead of QWidget
    Game game;
    game.show();

    return app.exec();
}
