#include "GameBoard.h"
#include "math.h"
#include <iostream>
#include <iomanip>

#include <Ship.h>
#include <QTime>
#include <QDebug>
#include <ctime>

using namespace std;
using namespace Base;

int GameBoard::nullField = -100;

GameBoard::GameBoard(QObject* obj,int size) : QObject(obj),m_size(size),curr_id(0)
{
    initializeGame();
}


GameBoard::~GameBoard()
{
  cout<<"Clearing game board" <<endl;
  clearBoard();
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

MoveResult GameBoard::validateMove(int x, int y)
{
  int& field = fieldAt(x,y);
  bool isDestroyed;
  MoveResult result = INCORRECT_COORDINATES;
  if(field != nullField)
  {
    if(field > 0)
    {
      QHash<int,Ship>::iterator it = m_ships.find(field);
      while (it != m_ships.end() && it.key() == field) {
	it.value().hit();
	isDestroyed = it.value().isDestroyed();
        field = -(int)SHIP_HIT;
	if(isDestroyed)
	{
	  m_ships.erase(it);
	  if(m_ships.isEmpty())

            result = ALL_SHIPS_DESTROYED;
	  else
          {
              emit shipDestroyed();
            result = SHIP_DESTROYED;
          }
	}	
	else
          result = SHIP_HIT;
        break;
      }
    }
    else if(field == 0)
    {
        fieldAt(x,y) = -(int)MISSED;
      result = MISSED;
    }
    else
        result = INCORRECT_COORDINATES;
  }
  else
    result = INCORRECT_COORDINATES;
  if(result!=INCORRECT_COORDINATES)
  {
    emit boardChanged();
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

int GameBoard::addShip(Ship newShip)
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
  if(ret == false)
      return 0;
  else
      return newShip.getShipId();
}

bool GameBoard::markShipOnBoard(Ship newShip)
{
    QPair<Position,Position> coords;
    if(validateShipPosition(newShip,coords))
    {
	for(int i=coords.first.first;i<=coords.second.first;i++)
	{
	  for(int j=coords.first.second;j<=coords.second.second;j++)
	  {
//	    cout <<"Drawing field " <<i<<" "<<j<<endl;
            fieldAt(i,j) = newShip.getShipId();
	  }
	}
        return true;
    }
    else return false;
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
      if(fieldAt(i,j) != 0 || !areNeighbourFieldsFree(i,j)) { isFree = false; break;}
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
    qDebug()<<"GENERATE BOARD FUNC "<<m_positionsGenerator.size();
    for(int i=0;i < m_size*m_size ;i++)
        m_positionsGenerator.append(i);

    QHashIterator<int,int> it(m_shipTypeCount);

    QList<int> keys = m_shipTypeCount.keys();

    for(int i = keys.size() - 1;i >=0 ;i--)
    {
        bool validCoords = true;
        int value = m_shipTypeCount.take(i);
        cout<<"Ship type "<<i+1<<" type count: "<<value<<endl;
        for(int i = 0; i < value; i++)
        {
            do
            {
                cout<<"Checking coords ";
                ShipType type = (ShipType)(i);
                Direction direction = (Direction)(random()%4);
                Ship ship(type,direction);
                int rand = random() % m_positionsGenerator.size();
                int rand_val = m_positionsGenerator.takeAt(rand);
                int x = rand_val / m_size;
                int y = rand_val % m_size;
//                cout<<x<<" "<<y<<endl;
                ship.setPosition(x,y);
                qDebug()<<"Entering direction loop. LEFT fields "<<m_positionsGenerator.size();
                for(int i=0;i<4;i++)
                {
                    ship.setDirection((Direction)((int)direction+i >= 4 ? (direction+i)-4 : direction+i ));
                    qDebug()<<"Ship direction "<<ship.getDirection();
                    validCoords = addShip(ship);
                    if(validCoords)
                    {
                        // remove values from generator
                        if(ship.getDirection() == DOWN || ship.getDirection() == UP)
                        {
                            for(int i=0;i<m_size;i++)
                            {
                                if(ship.getShipId() == fieldAt(i,ship.getPosition().second))
                                {
//                                    qDebug()<<"Removing "<<i<< " "<<ship.
                                    m_positionsGenerator.removeOne(i*m_size + ship.getPosition().second);
                                }
                            }
                        }
                        else
                        {
                            for(int i=0;i<m_size;i++)
                            {
                                if(ship.getShipId() == fieldAt(ship.getPosition().first,i))
                                {
                                    m_positionsGenerator.removeOne(ship.getPosition().first*m_size + i);
                                }
                            }
                        }
                        break;
                    }
                }
                qDebug()<<"Out of direction loop";
                if(!validCoords)
                    m_positionsGenerator.append(rand);
            }while(!validCoords);
        }
    }
    boardChanged();
}

void GameBoard::savePlayerMoveResult(int x, int y, MoveResult result)
{
    Position pos;
    pos.first = x;
    pos.second = y;
    bool moveValid = validatePosition(pos);
    if(moveValid)
    {
        fieldAt(x,y,true) = -(int)result;
        emit boardChanged();
//        qDebug()<<this->objectName().toLatin1()<<" - IS SHIP DESTROYED "<<isShipDestroyed<<endl;

        if(result == ALL_SHIPS_DESTROYED)
        {
            emit gameFinished();
//            qDebug()<<"Emiting signal game finished";
        }
    }
}

MoveResult GameBoard::makeShot(int field)
{
    int x = field / m_size;
    int y = field % m_size;
    MoveResult res = validateMove(x,y);
    if(res != INCORRECT_COORDINATES)
    {
//        cout<<"Shot is correct: "<<int(res)<<endl;
    }
    return res;
}

void GameBoard::savePlayerMoveResult(int field, MoveResult result)
{
    int x = field / m_size;
    int y = field % m_size;
    savePlayerMoveResult(x,y,result);
}

int GameBoard::addShip(int sails)
{
    int id = 0;
    do
    {
//        cout<<"Checking coords ";
        ShipType type = (ShipType)(sails - 1);
        Direction direction = (Direction)(random()%4);
        Ship ship(type,direction);
        int x = random() % m_size;
        int y = random() % m_size;
//        cout<<x<<" "<<y<<endl;
        ship.setPosition(x,y);
        id = addShip(ship);
    }while(id == 0);
    boardChanged();
//    cout<<"Ship ID "<<id<<endl;
    return id;
}

int GameBoard::removeShipById(int id,bool updateBoard)
{

    QHash<int,Ship>::iterator it = m_ships.find(id);
//    cout << "Key "<<it.key();
    if(it!=m_ships.end() && it.key() == id)
    {
        Position pos = it.value().getPosition();
        Direction dir = it.value().getDirection();
//        cout << "Ship position "<<pos.first<< " "<<pos.second<<endl;
        if(dir == UP || dir == DOWN)
        {
            for(int i=0;i<m_size;i++)
            {
                if(fieldAt(i,pos.second) == id)
                {
                    fieldAt(i,pos.second) = 0;
                }
            }
        }
        else
        {
            for(int i=0;i<m_size;i++)
            {
                if(fieldAt(pos.first,i) == id)fieldAt(pos.first,i) = 0;
            }
        }
        if(updateBoard)boardChanged();
        return it.value().getType()+1;
        m_ships.remove(id);
    }
    else
        return 0;
}

bool GameBoard::moveShip(int id,int x,int y)
{
    QHash<int,Ship>::iterator it = m_ships.find(id);
    while (it != m_ships.end() && it.key() == id) {
        Ship ship = it.value();
        Position pos = ship.getPosition();
        ship.setPosition(pos.first+x,pos.second +y);
        removeShipById(id,false);
//        cout<<"Ship ID after deletion "<<ship.getShipId()<<endl;
        QPair<Position,Position> coords;
        if(validateShipPosition(ship, coords))
        {
                markShipOnBoard(ship);
                m_ships.insert(id,ship);
        }
        else
        {
            ship.setPosition(pos.first,pos.second);
            markShipOnBoard(ship);
            m_ships.insert(id,ship);
        }
        boardChanged();
        it++;
    }
    return false;
}

bool GameBoard::validateShipPosition(Ship newShip,QPair<Position,Position> &coords)
{
    if(validatePosition(newShip.getPosition()))
    {
      coords.first = newShip.getPosition();

      switch(newShip.getDirection())
      {
        case UP:
          coords.second = qMakePair<int,int>(coords.first.first - newShip.getType(),coords.first.second);
          break;
        case DOWN:
          coords.second = qMakePair<int,int>(coords.first.first + newShip.getType(),coords.first.second);
          break;
        case LEFT:
          coords.second = qMakePair<int,int>(coords.first.first,coords.first.second - newShip.getType());
          break;
        case RIGHT:
          coords.second = qMakePair<int,int>(coords.first.first,coords.first.second + newShip.getType());
          break;
      }
      if(validatePosition(coords.second))
      {
        sortCoords(coords);
        if(areFieldsFree(coords))
        {
            return true;
        }
        else
        {
            cout << "Fields are not free" << endl;
            return false;
        }
      }
      else return false;
    }
    else return false;
}

bool GameBoard::validateShipPosition(int id, int x, int y)
{
    bool ret = false;
    QPair<Position,Position> coords;
    QHash<int,Ship>::iterator it = m_ships.find(id);
    while (it != m_ships.end() && it.key() == id) {
        Ship ship = it.value();
        Position pos = ship.getPosition();
        removeShipById(id,false);
        ship.setPosition(pos.first+x,pos.second+y);
        ret = validateShipPosition(ship,coords);
        ship.setPosition(pos.first,pos.second);
        markShipOnBoard(ship);
        m_ships.insert(id,ship);
        it++;
    }
    return ret;
}

bool GameBoard::rotateShip(int id, bool direction)
{
    bool ret = false;
    QHash<int,Ship>::iterator it = m_ships.find(id);
    while (it != m_ships.end() && it.key() == id) {
        Ship ship = it.value();
        Position pos = ship.getPosition();
        Direction dir = ship.getDirection();
        int directionChanged = dir + (direction ? 1: -1);
        if(directionChanged < 0) directionChanged += 4;
        else if(directionChanged >= 4) directionChanged-=4;
        removeShipById(id,false);
        Position temp = Position(pos.first,pos.second);
        ship.setDirection((Direction)directionChanged);
//        qDebug()<<"Ship direction "<<ship.getDirection();
        QPair<Position,Position> coords;
        ret = validateShipPosition(ship, coords);
        if(ret)
        {
                markShipOnBoard(ship);
                m_ships.insert(id,ship);
                boardChanged();
        }
        else
        {
            ship.setPosition(pos.first,pos.second);
            ship.setDirection(dir);
            markShipOnBoard(ship);
            m_ships.insert(id,ship);
        }
        it++;
    }
    return ret;
}

bool GameBoard::validateRotation(int id, bool direction)
{
    bool ret = false;
    QHash<int,Ship>::iterator it = m_ships.find(id);
    while (it != m_ships.end() && it.key() == id) {
        Ship ship = it.value();
        Position pos = ship.getPosition();
        Direction dir = ship.getDirection();
        int directionChanged = dir + (direction ? 1: -1);
        if(directionChanged < 0) directionChanged += 4;
        else if(directionChanged >= 4) directionChanged-=4;
        removeShipById(id,false);
        Position temp = Position(pos.first,pos.second);
        ship.setDirection((Direction)directionChanged);
//        qDebug()<<"Ship direction "<<ship.getDirection();
        QPair<Position,Position> coords;
        ret = validateShipPosition(ship, coords);
        ship.setPosition(pos.first,pos.second);
        ship.setDirection(dir);
        markShipOnBoard(ship);
        m_ships.insert(id,ship);
        it++;
    }
    return ret;
}

void GameBoard::clearBoard()
{
    m_board.clear();
    m_boardEnemy.clear();
    m_ships.clear();
    m_positionsGenerator.clear();
    curr_id = 0;
}

void GameBoard::initializeGame()
{
    for(int i=0;i<m_size;i++)
      for(int j=0;j<m_size;j++)
        m_board.append(0);

    for(int i=0;i<m_size;i++)
      for(int j=0;j<m_size;j++)
        m_boardEnemy.append(0);

    m_shipTypeCount.insert(3,1);
    m_shipTypeCount.insert(2,2);
    m_shipTypeCount.insert(1,3);
    m_shipTypeCount.insert(0,4);

}
