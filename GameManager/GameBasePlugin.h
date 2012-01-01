#ifndef GAMEBASEPLUGIN_H
#define GAMEBASEPLUGIN_H

#include <QDeclarativeExtensionPlugin>


//!  Klasa GameBasePlugin.
/*!
  Wtyczka dla interface'u.
*/
class GameBasePlugin : public QDeclarativeExtensionPlugin
{
        Q_OBJECT

    public:
        void registerTypes(const char *uri);
        
};

#endif // GAMEBASEPLUGIN_H
