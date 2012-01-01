#ifndef SHIP_H
#define SHIP_H

#include "Common.h"

namespace Base {
//!  Klasa Ship.
/*!
  Obsługa obiektów statków
*/
  class Ship
  {
    public:
      Ship(ShipType type = PATROL_BOAT,Direction direction = UP);
      void setPosition(int x,int y);
      Position& getPosition();
      ShipType getType();
      Direction getDirection();
      void setDirection(Direction dir);
      virtual ~Ship();
      bool isDestroyed();
      void hit();
      int getShipId();
      void setShipId(int Id);
    private:
      
      ShipType m_type;
      Direction m_direction;
      Position m_position;
      int m_fieldLeft;
      int m_Id;
  };
}

#endif // SHIP_H
