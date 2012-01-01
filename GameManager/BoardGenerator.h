#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H

#include <QList>
#include "GameBoard.h"

namespace Base
{
//!  Klasa BoardGenerator.
/*!
  Generowanie pola gry.
*/
    class BoardGenerator
    {
    public:
        BoardGenerator(QList<int>& board,int boardSize = 10);
        void initialize();
        void clear();
        QList<Base::Ship> generateBoard();
        QPair<Base::Position,Base::Direction> findBestCoordsForShip(int sails);
        void removeSurroundingFields(Base::Position,Base::Direction,int sails);
        bool validatePosition(Base::Position);
        void updateHistogram(QList<int>& board);
    private:
        QHash<int,int> m_positions;
        QList<Base::Position> m_NextHitList;
        QHash<int,int> m_shipTypeCount;
        QPair<Base::Position,Base::Direction> m_coords;
        QList<int>& _board;
        Base::GameBoard m_board;
        GameHistogram m_histogram;
    };

}

#endif // BOARDGENERATOR_H
