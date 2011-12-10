#ifndef SHIP_H
#define SHIP_H

#include <QPair>

namespace Base {
  typedef QPair<int,int> Position;
  class Ship
  {
    public:
      enum ShipType {
	PATROL_BOAT=0,
	SUBMARINE,
	DESTROYER,
	BATTLESHIP,
	AIRCRAFT_CARRIER
      };
      enum Direction {
        DOWN = 0,
        LEFT,
	UP,
	RIGHT
      };
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
