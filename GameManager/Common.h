#ifndef COMMON_H
#define COMMON_H
#include <QPair>

namespace Base
{
    enum MoveResult
    {
        INCORRECT_COORDINATES,
        MISSED,
        SHIP_HIT,
        SHIP_DESTROYED,
        ALL_SHIPS_DESTROYED
    };

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

    typedef QPair<int,int> Position;

    bool sortCoords(QPair<Position,Position>& coords);
}
#endif // COMMON_H
