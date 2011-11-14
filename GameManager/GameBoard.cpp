#include "GameBoard.h"
#include "math.h"
#include <iostream>
#include <iomanip>

#include <Ship.h>
#include <QTime>

using namespace std;
using namespace Base;

int GameBoard::nullField = -100;

GameBoard::GameBoard(int size) : m_size(size),curr_id(0)
{

    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
  cout<<"Creating board of size = "<<size<< " fields"<<endl;
  for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
      m_board.append(0);

  for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
      m_boardEnemy.append(0);

  m_shipTypeCount.insert(0,2);
  m_shipTypeCount.insert(1,2);
  m_shipTypeCount.insert(2,2);
  m_shipTypeCount.insert(3,1);
  m_shipTypeCount.insert(4,1);

  generateBoard();
}


GameBoard::~GameBoard()
{
  cout<<"Clearing game board" <<endl;
  m_board.clear();
}

int& GameBoard::fieldAt(int x,int y,bool board)
{
  int size = sqrt(m_board.size());
  if( x >= 0 && x < size && y >= 0 && y < size)
  {
      if(board)
          return m_boardEnemy[x*size + y];
      else
          return m_board[x*size + y];
  }
  else
    return nullField;
}

int GameBoard::getSize()
{
  return m_size;
}

GameBoard::MoveResult GameBoard::validateMove(int x, int y)
{
  int& field = fieldAt(x,y);
  bool isDestroyed;
  MoveResult result;
  if(field != nullField)
  {
    if(field > 0)
    {
      QHash<int,Ship>::iterator it = m_ships.find(field);
      while (it != m_ships.end() && it.key() == field) {
	it.value().hit();
	isDestroyed = it.value().isDestroyed();
        field = -1;
	if(isDestroyed)
	{
	  m_ships.erase(it);
	  cout<<"Ship count" << m_ships.size() <<endl;
	  if(m_ships.isEmpty())
            result = ALL_SHIPS_DESTROYED;
	  else
            result = SHIP_DESTROYED;
	}	
	else
          result = SHIP_HIT;
	++it;
      }
    }
    else
    {
      fieldAt(x,y) = -9;
      result = MISSED;
    }
  }
  else
    result = INCORRECT_COORDINATES;
  if(result!=INCORRECT_COORDINATES)
  {

  }
  return result;
}

void GameBoard::print(ostream& stream)
{
    stream << std::endl;
    for (int i = 0 ; i < this->getSize();i++)
    {
      for(int j = 0; j < this->getSize();j++)
      {
        stream << std::setw(3) << this->fieldAt(i,j)<< " ";
      }
        stream<<"\t";
        for(int j = 0; j < this->getSize();j++)
        {
        stream << std::setw(3) << this->fieldAt(i,j,true)<< " ";
        }
      stream << std::endl;
    }
}

bool GameBoard::addShip(Ship newShip)
{
  cout<< "AddShip func" <<endl;
  curr_id++;
  newShip.setShipId(curr_id);
  bool ret = markShipOnBoard(newShip);
  if(ret)
  {
    m_ships.insert(m_ships.count()+1,newShip);
  }
  else
  {
      curr_id--;
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
//	    cout <<"Drawing field " <<i<<" "<<j<<endl;
            fieldAt(i,j) = newShip.getShipId();
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
      if(fieldAt(i,j) != 0 || !areNeighbourFieldsFree(i,j)) isFree = false;
    }
  }
  return isFree;
}

bool GameBoard::areNeighbourFieldsFree(int x, int y)
{
//  cout<<"Checking neighbour fields"<<endl;
  // Check above field
  for(int i=x-1;i<=x+1;i++)
    for(int j=y-1;j<=y+1;j++)
      if(fieldAt(i,j) != nullField)
        if(fieldAt(i,j) != 0) return false;
  return true;
}

ostream& Base::operator<<(std::ostream& out,GameBoard& board)
{
  board.print(out);
  return out;
}

void GameBoard::generateBoard()
{
    QHashIterator<int,int> it(m_shipTypeCount);

    while(it.hasNext())
    {
        it.next();
        bool validCoords = true;
        cout<<it.key()+1<<" type count: "<<it.value()<<endl;
        for(int i = 0; i < it.value(); i++)
        {
            do
            {
                cout<<"Checking coords ";
                Ship::ShipType type = (Ship::ShipType)(it.key());
                Ship::Direction direction = (Ship::Direction)(qrand()%4);
                Ship ship(type,direction);
                int x = qrand() % m_size;
                int y = qrand() % m_size;
                cout<<x<<" "<<y<<endl;
                ship.setPosition(x,y);
                validCoords = addShip(ship);
            }while(!validCoords);
        }
    }
}

void GameBoard::savePlayerMoveResult(int x, int y, MoveResult result)
{
    bool moveValid = validateMove(x,y);
    if(moveValid)
    {
        fieldAt(x,y,true) = (int)result;
    }
}

void GameBoard::makeShot(int field)
{
    int x = field / m_size;
    int y = field % m_size;
    MoveResult res = validateMove(x,y);
    if(res != INCORRECT_COORDINATES)
    {
        cout<<"Shot is correct: "<<int(res)<<endl;
    }
}
