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

        Q_INVOKABLE QString testFunction() { return QString("hello"); }
    private:
        QList<int> readEnemyBoard();
        QList<int> readBoard();
        Base::GameBoard *m_board;

    signals:
        void dataChanged();
        
    public slots:
        void shot(int);
};
QML_DECLARE_TYPE(GameManager)

#endif // GAMEMANAGER_H
