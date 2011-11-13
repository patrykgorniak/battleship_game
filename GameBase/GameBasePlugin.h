#ifndef GAMEBASEPLUGIN_H
#define GAMEBASEPLUGIN_H

#include <QDeclarativeExtensionPlugin>

class GameBasePlugin : public QDeclarativeExtensionPlugin
{
        Q_OBJECT

    public:
        void registerTypes(const char *uri);
        
};

#endif // GAMEBASEPLUGIN_H
