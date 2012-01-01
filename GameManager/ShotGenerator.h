#ifndef SHOTGENERATOR_H
#define SHOTGENERATOR_H

#include "Common.h"

class GameHistogram;
namespace Base
{
//!  Klasa ShotGenerator.
/*!
  Obsługa procedury strzelania
*/
    class ShotGenerator
    {
    public:
        ShotGenerator(QList<int>& board);
        ~ShotGenerator();
       void initializeGenerator();
       void clearGenerator();
       void saveShotResult(int x,int y,MoveResult result);
       void saveShotResult(int field,MoveResult result);
       int getNextShot();
    private:
        Position lastShot;

        bool isDirectionDiscovered;
        bool isShipDestroyed;
        bool isShipHit;
        bool orientation;

        QList<int>& m_board;
        QList<int> m_positions;
        QList<Position> m_NextHitList;

        QPair<Position,Position> m_coords;

        GameHistogram* m_histogram;

        int m_size;

        void removeSurroundingFields(Position pos);
        bool validatePosition(Position pos);
        int fieldAt(int x,int y);
    };

}

#endif // SHOTGENERATOR_H
