#include "Ship.h"
#include <qpair.h>

using namespace Base;

Ship::Ship(ShipType type, Direction direction):m_type(type),m_direction(direction),m_fieldLeft(type+1)
{
  m_position.first = 0;
  m_position.second = 0;
}

Ship::~Ship()
{

}

void Ship::setPosition(int x, int y)
{
  m_position.first = x;
  m_position.second = y;
}

Position& Ship::getPosition()
{
  return m_position;
}

ShipType Ship::getType()
{
  return m_type;
}

Direction Ship::getDirection()
{
  return m_direction;
}

int Ship::getShipId()
{
  return m_Id;
}

void Ship::setShipId(int Id)
{
  m_Id = Id;
}

bool Ship::isDestroyed()
{
  return m_fieldLeft > 0? false:true;
}

void Ship::hit()
{
  if(m_fieldLeft > 0)
    --m_fieldLeft;
}

void Ship::setDirection(Direction dir)
{
    m_direction = dir;
}
