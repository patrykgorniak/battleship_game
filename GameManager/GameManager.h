#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QtDeclarative/QDeclarativeItem>

class GameManager : public QDeclarativeItem
{
        Q_OBJECT
        Q_DISABLE_COPY(GameManager)
    public:
        explicit GameManager(QDeclarativeItem *parent = 0);
        ~GameManager();
        Q_INVOKABLE QString testFunction() { return QString("hello"); }

    signals:
        
    public slots:
};
QML_DECLARE_TYPE(GameManager)

#endif // GAMEMANAGER_H
