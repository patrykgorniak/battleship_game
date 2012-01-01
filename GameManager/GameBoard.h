#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QList>
#include <QHash>
#include <iostream>
#include <iomanip>
#include "Ship.h"
#include "GameHistogram.h"


namespace Base
{
//!  Klasa GameBoard.
/*!
  Obsługa pola gry
*/
    class GameBoard: public QObject
    {
        Q_OBJECT
        public:
            Q_PROPERTY(QList<int> board READ readBoard)
            Q_PROPERTY(QList<int> enemyBoard READ readEnemyBoard)

            QList<int>& readBoard() { return m_board; }
            QList<int>& readEnemyBoard() { return m_boardEnemy; }

            GameBoard(QObject* obj = 0,int size=10);
//            GameBoard(GameBoard& boar);
            virtual ~GameBoard();
            int getSize();
            MoveResult validateMove(int x,int y);
            void savePlayerMoveResult(int x,int y,MoveResult result);
            void savePlayerMoveResult(int field,MoveResult result);
            void print(std::ostream& stream);
            int addShip(Ship newShip);
            int addShip(int sails);
            void addShips(QList<Ship> list);
            int removeShipById(int id,bool updateBoard = true); // TODO: CORRECT BUGS
            bool validatePosition(Position p); //
            MoveResult makeShot(int field);
            void generateBoard();
            bool moveShip(int id,int x,int y);
            bool rotateShip(int id,bool direction);
            bool validateRotation(int id,bool direction);

            bool validateShipPosition(Ship,QPair<Position,Position> &coords);
            bool validateShipPosition(int,int,int);
            void clearBoard();
            void initializeGame();
    signals:
            void boardChanged();
            void gameFinished();
            void shipDestroyed();

        private:
            QList<int> m_positionsGenerator;
            QList<int> m_board;
            QList<int> m_boardEnemy;
            QHash<int,Ship> m_ships;

            int m_size;

            int curr_id;
            int& fieldAt(int x,int y,bool board = false); // false value from m_board || true value from m_board2
            bool markShipOnBoard(Base::Ship newShip);
            bool areFieldsFree(QPair<Position,Position> coords);
            bool areNeighbourFieldsFree(int x,int y);
            static int nullField;
            QHash<int,int> m_shipTypeCount;
    };

    std::ostream& operator<<(std::ostream& out,Base::GameBoard& board);
}

#endif // GAMEBOARD_H
