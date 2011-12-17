#include "ShotGenerator.h"
#include "GameHistogram.h"
#include <cmath>
#include <QDebug>
using namespace Base;

ShotGenerator::ShotGenerator(QList<int> &board):m_board(board),m_size(sqrt(board.size()))
{
    m_histogram = new GameHistogram("histogram.txt",sqrt(board.size()));
    initializeGenerator();
}

ShotGenerator::~ShotGenerator()
{
    delete m_histogram;
    clearGenerator();
}

void ShotGenerator::initializeGenerator()
{
    m_histogram->readHistogram();
    m_positions = m_histogram->generateSortedList();
    isDirectionDiscovered = false;
    isShipDestroyed = false;
    isShipHit = false;
    orientation = false;
}

void ShotGenerator::clearGenerator()
{
    m_positions.clear();
    isDirectionDiscovered = false;
    isShipDestroyed = false;
    isShipHit = false;
    orientation = false;
    m_NextHitList.clear();
    m_histogram->saveHistogram();
}

void ShotGenerator::removeSurroundingFields(Position p)
{
    QPair<Position,Position> coords;
    if(orientation)
    {
        for(int i=p.second;i >= 0 ;i--)
        {
            Position temp = Position(p.first,i);
//            qDebug()<<"Matching "<<temp.first<<""<<temp.second;
            if(fieldAt(p.first,i) == -1 || fieldAt(p.first,i) == 0)
                break;
            else coords.first = temp;
        }
        for(int i=p.second;i < m_size ;i++)
        {
            Position temp = Position(p.first,i);
//            qDebug()<<"Matching "<<temp.first<<""<<temp.second;
            if(fieldAt(p.first,i) == -1 || fieldAt(p.first,i) == 0)
                break;
            coords.second = temp;
        }
//        qDebug()<<"REMOVING COORDS "<<coords;
    }
    else
    {
        for(int i=p.first;i >= 0 ;i--)
        {
            Position temp = Position(i,p.second);
//            qDebug()<<"Matching "<<temp.first<<""<<temp.second;
            if(fieldAt(i,p.second) == -1 || fieldAt(i,p.second) == 0 || !validatePosition(temp))
                break;
            coords.first = temp;
        }
        for(int i=p.first;i < m_size ;i++)
        {
            Position temp = Position(i,p.second);
//            qDebug()<<"Matching "<<temp.first<<""<<temp.second;
            if(fieldAt(i,p.second)== -1 || fieldAt(i,p.second) == 0 || !validatePosition(temp))
                break;
            coords.second = temp;
        }
//        qDebug()<<"REMOVING COORDS "<<coords;
    }
    sortCoords(coords);
//    qDebug()<<"COORDS "<<coords.first.first-1<<" "<<coords.second.first+1<<endl;
//    if(coords.first.first-1 < coords.second.first+1)qDebug()<<"OK";
    for(int i=coords.first.first-1;i<=coords.second.first+1;i++)
    {
        for(int j=coords.first.second - 1;j<=coords.second.second+1;j++)
        {
            Position temp = Position(i,j);
            if(validatePosition(temp))
            {
                if(fieldAt(i,j) == 0)
                {
//                    qDebug()<<"["<<i<<","<<j<<"]";
                    m_positions.removeOne(temp.first*m_size+temp.second);
//                    fieldAt(i,j,true) = -1;
                }
            }
        }
    }
}

bool ShotGenerator::validatePosition(Position p)
{
    if(p.first >= 0 && p.first < m_size && p.second >= 0 && p.second < m_size)
    {
      return true;
    }
    else return false;
}

int ShotGenerator::fieldAt(int x, int y)
{
    Position pos = qMakePair(x,y);
    if(validatePosition(pos))
        return m_board.at(x*m_size+y);
    else return -100;
}

void ShotGenerator::saveShotResult(int x, int y, MoveResult result)
{
    Position pos;
    pos.first = x;
    pos.second = y;
    bool moveValid = validatePosition(pos);
    if(moveValid)
    {

        qDebug()<<"Result "<<result;
        if(result == SHIP_HIT || result == SHIP_DESTROYED || result == ALL_SHIPS_DESTROYED)
        {
            qDebug()<<"hit "<<pos.first*m_size+pos.second;
            m_histogram->modifyHistogram(x*m_size+y);
        }

        if(result == SHIP_DESTROYED)
        {
            // TODO: mark surrounding fields , its certain that ship is not there
//            cout<< "SHIP DESTROYED"<<endl;
            if(!isDirectionDiscovered && isShipHit)
            {
                if(lastShot.first == pos.first)
                    orientation = true;
                else
                    orientation = false;
            }
            m_NextHitList.clear();
            isShipHit = false;
            isShipDestroyed = false;
            isDirectionDiscovered = false;
            removeSurroundingFields(pos);
            orientation = false;
        }
        else if(result == SHIP_HIT && !isShipHit)
        {
            isShipHit = true;
            lastShot = Position(x,y);
            m_NextHitList.append(Position(x+1,y));
            m_NextHitList.append(Position(x-1,y));
            m_NextHitList.append(Position(x,y - 1));
            m_NextHitList.append(Position(x,y + 1));
            for(int i=m_NextHitList.size()-1;i>=0;i--)
            {
                Position temp = m_NextHitList.at(i);
                cout<<temp.first<< " " << temp.second << endl;
                if(!validatePosition(m_NextHitList.at(i)) || fieldAt(temp.first,temp.second) < 0)
                {
                    cout<<"Invalid position deleting"<<endl;
                    m_NextHitList.removeAt(i);
                }
            }
            qDebug()<<m_NextHitList;
        }
        else if(result == SHIP_HIT && isShipHit)
        {
            m_NextHitList.clear();
            isDirectionDiscovered = true;
            m_coords = qMakePair(lastShot,pos);
            sortCoords(m_coords);
            if(x == lastShot.first)
            {
                for(int i=m_coords.first.second - 1;i >= 0;i--)
                {
                    Position temp = Position(m_coords.first.first,i);
                    if(validatePosition(temp) && fieldAt(temp.first,temp.second) >= 0)
                        m_NextHitList.append(temp);
                    else if(validatePosition(temp) && fieldAt(temp.first,temp.second) < 0)
                    {
                        break;
//                        cout<<"Shot has been already carried out"<<endl;
                    }
                }
                for(int i=m_coords.second.second + 1;i < m_size;i++)
                {
                    Position temp = Position(m_coords.first.first,i);
                    if(validatePosition(temp) && fieldAt(temp.first,temp.second) >= 0)
                        m_NextHitList.append(temp);
                    else if(validatePosition(temp) && fieldAt(temp.first,temp.second) < 0)
                    {
                        break;
//                        cout<<"Shot has been already carried out"<<endl;
                    }
                }
//                qDebug()<<m_NextHitList;
                orientation = true; //horizontal
            }
            else
            {
                for(int i=m_coords.first.first - 1;i >= 0;i--)
                {
                    Position temp = Position(i,m_coords.first.second);
                    if(validatePosition(temp) && fieldAt(temp.first,temp.second) >= 0)
                        m_NextHitList.append(temp);
                    else if(validatePosition(temp) && fieldAt(temp.first,temp.second) < 0)
                    {
                        break;
//                        cout<<"Shot has been already carried out"<<endl;
                    }
                }
                for(int i=m_coords.second.first + 1;i < m_size;i++)
                {
                    Position temp = Position(i,m_coords.first.second);
                    if(validatePosition(temp) && fieldAt(temp.first,temp.second) >= 0)
                        m_NextHitList.append(temp);
                    else if(validatePosition(temp) && fieldAt(temp.first,temp.second) < 0)
                    {
                        break;
//                        cout<<"Shot has been already carried out"<<endl;
                    }

                }
//                qDebug()<<m_NextHitList;
                orientation = false;
            }

        }
        else if(result == MISSED && isShipHit && isDirectionDiscovered)
        {
            if(orientation)
            {
                for(int i=m_coords.first.second - 1;i >=0;i--)
                    m_NextHitList.removeOne(qMakePair(m_coords.first.first,i));
            }
            else
            {
                for(int i=m_coords.first.first - 1;i >=0;i--)
                    m_NextHitList.removeOne(qMakePair(i,m_coords.first.second));
            }
        }
    }
}

void ShotGenerator::saveShotResult(int field, MoveResult result)
{
    int x = field / m_size;
    int y = field % m_size;
    saveShotResult(x,y,result);
}

int ShotGenerator::getNextShot()
{
    int val;
    qDebug()<<"Next List size "<<m_NextHitList.size();
    qDebug()<<"m_positions list size"<<m_positions.size();
    if(isShipHit && m_NextHitList.size() > 0)
    {
//        cout<<"list shot"<<endl;
        Position pos = m_NextHitList.takeFirst();
        val = pos.first* m_size + pos.second;
        m_positions.removeOne(val);
    }
    else if(m_positions.size() > 0)
    {
//        cout<<"random shot"<<endl;
        val = m_positions.takeLast();
    }
    return val;
}
