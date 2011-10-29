#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QList>
#include <QPair>
#include <QHash>
#include <iostream>
#include <iomanip>
#include "Ship.h"
namespace Base
{
  typedef QPair<int,bool> Field;
  class GameBoard
  {
  private:
    QList<Field> m_board;
    QHash<int,Ship> m_ships;
    int m_size;
    Field& fieldAt(int x,int y);
    bool markShipOnBoard(Base::Ship newShip);
    bool validatePosition(Position p);
    bool sortCoords(QPair<Position,Position>& coords);
    bool areFieldsFree(QPair<Position,Position> coords);
    bool areNeighbourFieldsFree(int x,int y);
    static Field nullField;
  public:
    GameBoard(int size=10);
    virtual ~GameBoard();
    int getSize();
    bool validateMove(int x,int y);
    void print(std::ostream& stream);
    bool addShip(Ship newShip);
  };
  
  std::ostream& operator<<(std::ostream& out,Base::GameBoard& board);
};

#endif // GAMEBOARD_H
