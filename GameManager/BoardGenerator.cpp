#include "BoardGenerator.h"
#include <QDebug>

using namespace Base;

BoardGenerator::BoardGenerator(QList<int>& board,int boardSize):_board(board),m_board(NULL,boardSize),m_histogram("boardHistogram.txt",boardSize)
{
    initialize();
}

void BoardGenerator::initialize()
{
    m_board.clearBoard();
    m_histogram.readHistogram();
    m_positions = m_histogram.getHistogramHashTable();
    m_board.initializeGame();

    m_shipTypeCount.insert(3,1);
    m_shipTypeCount.insert(2,2);
    m_shipTypeCount.insert(1,3);
    m_shipTypeCount.insert(0,4);
}

void BoardGenerator::clear()
{
    updateHistogram(_board);
    m_histogram.clearHistogram();
    m_positions.clear();
    m_board.clearBoard();
}

QList<Base::Ship> BoardGenerator::generateBoard()
{
    QList<Ship> ships;
    QList<int> keys = m_shipTypeCount.keys();

    qDebug()<<keys;

    for(int i=0;i<keys.size();i++)
    {
        int count = m_shipTypeCount.take(keys[i]);

        for(int j=0;j<count;j++)
        {
            QPair<Base::Position,Base::Direction> position = findBestCoordsForShip(keys[i]);
            removeSurroundingFields(position.first,position.second,keys[i]);
            ships.append(Ship((ShipType)keys[i],position.second,position.first));

            qDebug()<<"Fields left "<<m_positions.size();
        }
    }
    return ships;
}

QPair<Base::Position,Base::Direction> BoardGenerator::findBestCoordsForShip(int sails)
{
    int maximum = -1;
    Position max_pos;
    Direction direction;
    int temp = 0;
    int count;
    qDebug()<<"Positions" <<m_positions;
    for(int i=0;i<m_board.getSize();i++)
    {
        // Poziome wyszukiwanie
        for(int j=0;j <m_board.getSize() - sails;j++)
        {
            count = 0;
            temp = 0;
            for(int k=0;k<=sails;k++)
            {
                int pos = i*m_board.getSize() + j + k;
                if(m_positions.contains(pos))
                {
                    temp+=m_positions.value(pos);
//                    qDebug()<<"Temp increase["<<pos<<"] = "<<temp;
                    count++;
                }
                else
                    break;
            }
//            qDebug()<<"Temp val: "<<temp;
            if(count == sails +1 && temp >= maximum && m_positions.contains(i*m_board.getSize()+ j))
            {
                maximum = temp;
                max_pos = qMakePair(i,j);
                direction = RIGHT;
                qDebug()<<"Maximum "<<maximum<<" Position "<<max_pos << " Sails: "<<sails+1;
            }
        }
    }


    qDebug()<<"pionowe wyszykiwanie ";
//     Pionowe wyszukiwanie
    for(int i=0;i<m_board.getSize();i++)
    {
        for(int j=0;j <m_board.getSize() - sails;j++)
        {
            count = 0;
            temp = 0;
            for(int k=0;k<=sails;k++)
            {
                int pos = (j+k)*m_board.getSize() + i;
//                qDebug()<<"Position ["<<pos<<"]";
                if(m_positions.contains(pos))
                {
                    temp+=m_positions.value(pos);
//                        qDebug()<<"Temp increase["<<pos<<"] = "<<temp;
                    count++;
                }
                else
                    break;
            }
    //            qDebug()<<"Temp val: "<<temp;
            if(count == sails +1 && temp >= maximum && m_positions.contains(j*m_board.getSize()+ i))
            {
                maximum = temp;
                max_pos = qMakePair(j,i);
                direction = DOWN;
//                qDebug()<<"Maximum "<<maximum<<" Position "<<max_pos << " Sails: "<<sails+1;
            }
        }
    }
//    qDebug()<<m_positions;
    qDebug()<<"Maximum "<<maximum<<" Position "<<max_pos << " Sails: "<<sails+1;
    return qMakePair(max_pos,direction);
}

void BoardGenerator::removeSurroundingFields(Base::Position pos, Direction dir, int sails)
{
    Position start;
    Position end;
    if(dir == DOWN)
    {
        for(int i=pos.first - 1;i<=pos.first+sails+1;i++)
        {
            for(int j=pos.second - 1;j<=pos.second+1;j++)
            {
                Position temp = qMakePair(i,j);
                if(validatePosition(temp))
                {
                    qDebug()<<"removing ["<<i<<","<<j<<"]";
                    m_positions.remove(i*m_board.getSize()+j);
                }
            }
        }
    }
    else // RIGHT
    {
        for(int i=pos.first - 1;i<=pos.first+1;i++)
        {
            for(int j=pos.second - 1;j<=pos.second+sails+1;j++)
            {
                Position temp = qMakePair(i,j);
                if(validatePosition(temp))
                {
                    qDebug()<<"removing ["<<i<<","<<j<<"]";
                    m_positions.remove(i*m_board.getSize()+j);
                }
            }
        }
    }
}

bool BoardGenerator::validatePosition(Position p)
{
    if(p.first >= 0 && p.first < m_board.getSize() && p.second >= 0 && p.second < m_board.getSize())
    {
      return true;
    }
    else return false;
}

void BoardGenerator::updateHistogram(QList<int> &board)
{
    for(int i=0;i<board.size();i++)
    {
        if(board.at(i) == -MISSED)
        {
            // add 1
            m_histogram.setHistogram(i,m_histogram.getHistogram(i) - 1);
        }
        else if(board.at(i) == 0)
        {
            m_histogram.setHistogram(i,m_histogram.getHistogram(i)+3);
            // add 3
        }
        else if(board.at(i) == -SHIP_HIT && board.at(i) == -SHIP_DESTROYED && board.at(i) == -ALL_SHIPS_DESTROYED)
        {
            m_histogram.setHistogram(i,m_histogram.getHistogram(i)-2);
            // sub ??
        }
    }
    m_histogram.saveHistogram();
}
