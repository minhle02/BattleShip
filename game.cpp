#include "game.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
{
    p1 = new Player(nullptr, "Human player");
    p2 = new ComputerPlayer(nullptr, "Computer player");
    display = new DisplayPlayer(p1,p2);
    srand(time(NULL));
    int seed = rand() % 100;
    p1->GenerateRandomShip(seed);
    seed = rand() % 100 + 100;
    p2->GenerateRandomShip(seed);
    display->show();
}

Game::~Game()
{
}

