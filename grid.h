#ifndef GRID_H
#define GRID_H
#include <QVector>
#include <stdexcept>

enum Ship{None, Fire, Hit, Carrier, Destroyer, Submarine, Cruiser, Battleship};

struct GridSquare {
    Ship ship;
    int index;
};

class Grid
{
public:
    explicit Grid(int size = 0);
    void addShip(Ship ship, int index);
    Ship ShipAt(int index);
    //void ChangeSquare(Ship ship, int index);
private:
    QVector<GridSquare> board;
    int size;
};

#endif // GRID_H
