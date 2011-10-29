#include "GameBoard.h"
#include "math.h"
#include <iostream>
#include <iomanip>
#include <Ship.h>

using namespace std;
using namespace Base;

Field GameBoard::nullField = qMakePair<int,bool>(-1,false);

GameBoard::GameBoard(int size) : m_size(size)
{
  cout<<"Creating board of size = "<<size<< " fields"<<endl;
  for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
      m_board.append(Field());
}


GameBoard::~GameBoard()
{
  cout<<"Clearing game board" <<endl;
  m_board.clear();
}

Field& GameBoard::fieldAt(int x,int y)
{
  int size = sqrt(m_board.size());
  if( x >= 0 && x < size && y >= 0 && y < size)
  {
    return m_board[x*size + y];
  }
  else
    return nullField;
}

int GameBoard::getSize()
{
  return m_size;
}

bool GameBoard::validateMove(int x, int y)
{
//   if(fieldAt(x,y) != 
// TODO if the ship is hit decrease val in Ship class and check if the ship is Destroyed:D
}

void GameBoard::print(ostream& stream)
{
    stream << std::endl;
    for (int i = 0 ; i < this->getSize();i++)
    {
      for(int j = 0; j < this->getSize();j++)
      {
	stream << std::setw(3) << this->fieldAt(i,j).first<< " ";
      }
      stream << std::endl;
    }
}

bool GameBoard::addShip(Ship newShip)
{
  cout<< "AddShip func" <<endl;
  int Id = m_ships.count() + 1;
  newShip.setShipId(Id);
  bool ret = markShipOnBoard(newShip);
  if(ret)
  {
    m_ships.insert(m_ships.count()+1,newShip);
  }
  return ret;
}

bool GameBoard::markShipOnBoard(Ship newShip)
{
  if(validatePosition(newShip.getPosition()))
  {
    QPair<Position,Position> coords;
    coords.first = newShip.getPosition();
    switch(newShip.getDirection())
    {
      case Ship::UP:
	coords.second = qMakePair<int,int>(coords.first.first - newShip.getType(),coords.first.second);
	break;
      case Ship::DOWN:
	coords.second = qMakePair<int,int>(coords.first.first + newShip.getType(),coords.first.second);
	break;
      case Ship::LEFT:
	coords.second = qMakePair<int,int>(coords.first.first,coords.first.second - newShip.getType());
	break;
      case Ship::RIGHT:
	coords.second = qMakePair<int,int>(coords.first.first,coords.first.second + newShip.getType());
	break;
    }
    if(validatePosition(coords.second))
    {
      if(sortCoords(coords) && areFieldsFree(coords))
      {
	for(int i=coords.first.first;i<=coords.second.first;i++)
	{
	  for(int j=coords.first.second;j<=coords.second.second;j++)
	  {
	    cout <<"Drawing field " <<i<<" "<<j<<endl;
	    fieldAt(i,j).first = newShip.getShipId();
	  }
	}
      }
      else 
      {
	cout << "Somethin went wrong" << endl;
	return false;
      }
    }
    else return false;
  }
  else return false;
  return true;
}

bool GameBoard::sortCoords(QPair< Position, Position >& coords)
{
  if(coords.first.first == coords.second.first)
  {
    cout<< " X is the same" <<endl;
    Position temp = coords.first;
    cout << coords.second.first << " "<<coords.second.second<<endl;
    if(temp.second > coords.second.second)
    {
      coords.first = coords.second;
      coords.second = temp;
    }
  }
  else if(coords.first.second == coords.second.second)
  {
    cout<< " Y is the same" <<endl;
    Position temp = coords.first;
    cout << coords.second.first << " "<<coords.second.second<<endl;
    if(temp.first > coords.second.first)
    {
      coords.first = coords.second;
      coords.second = temp;
    }
  }
  else
    return false;
  return true;
}


bool GameBoard::validatePosition(Position p)
{
  if(p.first >= 0 && p.first < m_size && p.second >= 0 && p.second < m_size)
  {
    return true;
  }
  else return false;
}

bool GameBoard::areFieldsFree(QPair< Position, Position > coords)
{
  bool isFree = true;
  for(int i=coords.first.first;i<=coords.second.first;i++)
  {
    for(int j=coords.first.second;j<=coords.second.second;j++)
    {
      if(fieldAt(i,j).first != 0 || !areNeighbourFieldsFree(i,j)) isFree = false;
    }
  }
  return isFree;
}

bool GameBoard::areNeighbourFieldsFree(int x, int y)
{
  cout<<"Checking neighbour fields"<<endl;
  // Check above field
  for(int i=x-1;i<=x+1;i++)
    for(int j=y-1;j<=y+1;j++)
      if(fieldAt(i,j) != nullField)
	if(fieldAt(i,j).first != 0) return false;
  return true;
}

ostream& Base::operator<<(std::ostream& out,GameBoard& board)
{
  board.print(out);
  return out;
}
