#include <QApplication>
#include "game.h"
#include "QGridLayout"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game;
   game.show();

    return a.exec();
}
