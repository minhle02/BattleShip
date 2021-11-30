#include "player.h"


Player::Player(QObject *parent, QString userName) : QObject(parent),
    name(userName), shipBoard(SIZE*SIZE), firing(SIZE*SIZE)
{
    shipNum = 0;
}

bool Player::addShip(Ship ship, int startIndex, Direction d)
{
    if (startIndex < 0 || startIndex >= SIZE*SIZE)
        throw std::runtime_error("Invalid index");
    int shipLength = ShipSize(ship);
    if (shipLength == 0) {
        return true;
    }
    int index = -1;
    int row = startIndex / SIZE;
    int col = startIndex % SIZE;
    if (d == vertical) {
        if (row + shipLength >= SIZE)
            return false;
        for (int i = 0; i < shipLength; i++) {
            index = (row+i)*SIZE + col;
            if (shipBoard.ShipAt(index) != None) {
                return false;
            }
        }

        for (int i = 0; i < shipLength; i++) {
            index = (row+i)*SIZE + col;
            shipBoard.addShip(ship, index);
            emit SendShipPos(index, ship);
        }
    } else if (d == horizontal){
        if (col+shipLength >= SIZE)
            return false;
        for (int i = 0; i < shipLength; i++) {
            index = row*SIZE + col + i;
            if (shipBoard.ShipAt(index) != None) {
                return false;
            }
        }
        for (int i = 0; i < shipLength; i++) {
            index = row*SIZE + col + i;
            shipBoard.addShip(ship, index);
            emit SendShipPos(index,ship);
        }
    }
    shipNum++;
    return true;
}

bool Player::FireAt(Player &other, int index)
{
    if (index >= SIZE*SIZE || index < 0)
        throw std::runtime_error("Invalid index");
    Ship s = other.shipBoard.ShipAt(index);
    if (s == Fire || s == Hit)
        return false;
    if (s == None) {
        firing.addShip(Fire,index);
        other.shipBoard.addShip(Fire,index);
        emit SendMessage(this->name + ", missed");
        emit SendCoordinate(index, false);
    } else {
        other.shipNum--;
        QString message = this->name + " hit " + ShipName(s) + " ship of " + other.name;
        emit SendMessage(message);
        int row = index / SIZE;
        int col = index % SIZE;
        int r1 = row, r2 = row-1, c1 = col+1, c2 = col-1;
        int position = 0;
        while (1) {
            if (r1 >= 0 && r1 < SIZE && other.shipBoard.ShipAt(r1*SIZE+col) == s) {
                position = r1*SIZE + col;
                other.shipBoard.addShip(Hit,position);
                firing.addShip(Hit,position);
                emit SendCoordinate(position, true);
                r1++;
                continue;
            }
            if (r2 >= 0 && r2 < SIZE && other.shipBoard.ShipAt(r2*SIZE + col) == s) {
                position = r2*SIZE + col;
                other.shipBoard.addShip(Hit,position);
                firing.addShip(Hit,position);
                emit SendCoordinate(position, true);
                r2--;
                continue;
            }
            if (c1 >= 0 && c1 < SIZE && other.shipBoard.ShipAt(row*SIZE + c1) == s) {
                position = row*SIZE + c1;
                other.shipBoard.addShip(Hit,position);
                firing.addShip(Hit,position);
                emit SendCoordinate(position, true);
                c1++;
                continue;
            }
            if (c2 >= 0 && c2 < SIZE && other.shipBoard.ShipAt(row*SIZE + c2) == s) {
                position = row*SIZE + c2;
                other.shipBoard.addShip(Hit,position);
                firing.addShip(Hit,position);
                emit SendCoordinate(position, true);
                c2--;
                continue;
            }
            break;
        }
        if (other.IsLost()) {
            emit Win();
        }
    }
    return true;
}

void Player::GenerateRandomShip(int seed)
{
    srand(seed);
    int index, randNum;
    Direction d = vertical;
    Ship shipList[5] = {Carrier,Cruiser,Destroyer,Battleship,Submarine};
    for (int i = 0; i < 5; i++) {
        do {
            index = rand() % (SIZE*SIZE);
            randNum = rand() % 2;
            d = (randNum == 1) ? vertical : horizontal;
        } while (!addShip(shipList[i],index,d));
    }
    emit SendMessage(this->name + " ships are placed on board");

}

int Player::ShipSize(Ship ship)
{
    if (ship == Cruiser)
        return 3;
    if (ship == Battleship)
        return 4;
    if (ship == Carrier)
        return 5;
    if (ship == Destroyer)
        return 3;
    if (ship == Submarine)
        return 2;
    return 0;
}

QString Player::ShipName(Ship ship)
{
    if (ship == Carrier)
        return "Carrier";
    if (ship == Cruiser)
        return "Cruiser";
    if (ship == Destroyer)
        return "Destroyer";
    if (ship == Battleship)
        return "Battleship";
    if (ship == Submarine)
        return "Submarine";
    return "Unknown Ship";
}



ComputerPlayer::ComputerPlayer(QObject *parent, QString userName) : Player(parent,userName)
{
}

void ComputerPlayer::RandomFire(Player &other)
{
    srand(time(NULL));
    int index;
    do {
        index = rand() % (SIZE*SIZE);
    } while(!this->FireAt(other,index));
    emit SendFirePos(index);
}
