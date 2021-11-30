#include "game.h"
#include "displayplayer.h"

#include <QApplication>
#include <QTabWidget>
#include <QMainWindow>
#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        Game w;
        return a.exec();
    } catch (std::runtime_error e) {
        std::cout<<e.what() << std::endl;
    }
}
