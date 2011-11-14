#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <GameBase.h>
#include <QtDeclarative/QDeclarativeItem>

class GameManager : public QDeclarativeItem
{
        Q_OBJECT
        Q_DISABLE_COPY(GameManager)
    public:

        Q_PROPERTY(QList<int> boardEnemy READ readEnemyBoard)
        Q_PROPERTY(QList<int> board READ readBoard)

        explicit GameManager(QDeclarativeItem *parent = 0);
        ~GameManager();

        Q_INVOKABLE QString testFunction() { return QString("hello"); }
    private:
        QList<int> readEnemyBoard();
        QList<int> readBoard();

        Base::GameBoard *m_board;

    signals:
        
    public slots:
};
QML_DECLARE_TYPE(GameManager)

#endif // GAMEMANAGER_H
