#include "grid.h"


Grid::Grid(int size) : size(size)
{
    if (size < 0) {
        throw std::runtime_error("Size less than 0");
    }
    for (int i = 0; i < size; i++) {
        GridSquare s;
        s.ship = None;
        s.index = i;
        board.push_back(s);
    }
}

void Grid::addShip(Ship ship, int index)
{
    if (index < 0 || index > this->size) {
        throw std::runtime_error("Index out of bound");
    }
    GridSquare s;
    s.ship = ship;
    s.index = index;
    board.replace(index,s);
}

Ship Grid::ShipAt(int index)
{
    if (index < 0 || index > size)
        throw std::runtime_error("Index out of bound");
    return board.at(index).ship;
}

//void Grid::ChangeSquare(Ship ship, int index)
//{
//    GridSquare s;
//    s.ship = ship;
//    s.index = index;
//    board.replace(index,s);
//}

