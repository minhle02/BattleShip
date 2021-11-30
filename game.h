#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "displayplayer.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
private:
    Player *p1;
    ComputerPlayer *p2;
    DisplayPlayer *display;
};
#endif // GAME_H
