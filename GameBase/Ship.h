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
	DOWN,
	UP,
	LEFT,
	RIGHT
      };
      Ship(ShipType type = PATROL_BOAT,Direction direction = UP);
      void setPosition(int x,int y);
      Position& getPosition();
      ShipType getType();
      Direction getDirection();
      virtual ~Ship();
      bool isDestroyed();
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
