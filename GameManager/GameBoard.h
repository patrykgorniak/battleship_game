#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QList>
#include <QPair>
#include <QHash>
#include <iostream>
#include <iomanip>
#include "Ship.h"

namespace Base
{
    typedef QPair<int,int> Field;
    class GameBoard
    {
        public:
            enum MoveResult
            {
                INCORRECT_COORDINATES,
                MISSED,
                SHIP_HIT,
                SHIP_DESTROYED,
                ALL_SHIPS_DESTROYED
            };

            Q_PROPERTY(QList<int> board READ readBoard)
            Q_PROPERTY(QList<int> enemyBoard READ readEnemyBoard)

            QList<int> readBoard() { return m_board; }
            QList<int> readEnemyBoard() { return m_boardEnemy; }

            GameBoard(int size=10);
            virtual ~GameBoard();
            int getSize();
            MoveResult validateMove(int x,int y);
            void savePlayerMoveResult(int x,int y,MoveResult result);
            void print(std::ostream& stream);
            bool addShip(Ship newShip);
            bool validatePosition(Position p);
            void makeShot(int field);
    signals:
            void boardChanged();

        private:
            QList<int> m_board;
            QList<int> m_boardEnemy;
            QHash<int,Ship> m_ships;
            int m_size;
            int& fieldAt(int x,int y,bool board = false); // false value from m_board || true value from m_board2
            bool markShipOnBoard(Base::Ship newShip);
            bool sortCoords(QPair<Position,Position>& coords);
            bool areFieldsFree(QPair<Position,Position> coords);
            bool areNeighbourFieldsFree(int x,int y);
            static int nullField;
            QHash<int,int> m_shipTypeCount;
            void generateBoard();
            int curr_id;
    };

    std::ostream& operator<<(std::ostream& out,Base::GameBoard& board);
}

#endif // GAMEBOARD_H
