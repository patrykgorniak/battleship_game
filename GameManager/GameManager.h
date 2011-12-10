#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <GameBase.h>
#include <QtDeclarative/QDeclarativeItem>
#include <QDebug>

class GameManager : public QDeclarativeItem
{
        Q_OBJECT
        Q_DISABLE_COPY(GameManager)
    public:

        Q_PROPERTY(QList<int> boardEnemy READ readEnemyBoard NOTIFY dataChanged)
        Q_PROPERTY(QList<int> board READ readBoard NOTIFY dataChanged)

        explicit GameManager(QDeclarativeItem *parent = 0);
        ~GameManager();

        Q_INVOKABLE void generateBoard();
        Q_INVOKABLE int addShip(int);
        Q_INVOKABLE int removeShip(int);
        Q_INVOKABLE bool moveShip(int,int,int);
        Q_INVOKABLE bool validateShipPosition(int,int,int);

    private:
        QList<int> readEnemyBoard();
        QList<int> readBoard();
        Base::GameBoard *m_board;
        Base::GameBoard *m_enemyBoard;

    signals:
        void dataChanged();
        void shipDestroyed();
        void gameFinished();
        
    public slots:
        void shot(int);
        void shotNotify();
};
QML_DECLARE_TYPE(GameManager)

#endif // GAMEMANAGER_H
