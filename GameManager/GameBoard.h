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
  typedef QPair<int,int> Field;
  class GameBoard
  {
  private:
    QList<int> m_board;
    QList<int> m_board2;
    QHash<int,Ship> m_ships;
    int m_size;
    int& fieldAt(int x,int y,bool board = false); // false value from m_board || true value from m_board2
    bool markShipOnBoard(Base::Ship newShip);
    bool sortCoords(QPair<Position,Position>& coords);
    bool areFieldsFree(QPair<Position,Position> coords);
    bool areNeighbourFieldsFree(int x,int y);
    static int nullField;
    QHash<int,int> m_shipTypeCount;
    void generateBoard();
    int curr_id;
  public:
    enum MoveResult 
    {
      INCORRECT_COORDINATES,
      MISSED,
      SHIP_HIT,
      SHIP_DESTROYED,
      ALL_SHIPS_DESTROYED
    };
    GameBoard(int size=10);
    virtual ~GameBoard();
    int getSize();
    MoveResult validateMove(int x,int y);
    void print(std::ostream& stream);
    bool addShip(Ship newShip);
    bool validatePosition(Position p);
  };
  
  std::ostream& operator<<(std::ostream& out,Base::GameBoard& board);
};

#endif // GAMEBOARD_H
