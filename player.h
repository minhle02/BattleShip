#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include "grid.h"
#include <cstdlib>
#include <ctime>
const int SIZE = 10;

enum Direction{vertical, horizontal};

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr, QString userName = "Unknown");
    bool addShip(Ship ship, int startIndex, Direction d);
    bool FireAt(Player& other,int index);
    void GenerateRandomShip(int seed = time(NULL));
    bool IsLost() {return shipNum == 0;}
private:
    QString name;
    Grid shipBoard;
    Grid firing;
    int shipNum;

    /*Helper function*/
    int ShipSize(Ship ship);
    QString ShipName(Ship ship);
signals:
    void SendMessage(QString mess);
    void SendCoordinate(int coord, bool isHit);
    void SendShipPos(int index, Ship ship);
    void Win();
};

class ComputerPlayer : public Player {
    Q_OBJECT
public:
    ComputerPlayer(QObject *parent = nullptr, QString userName = "Unknown");
    void RandomFire(Player& other);
signals:
    void SendFirePos(int index);
};

#endif // PLAYER_H
