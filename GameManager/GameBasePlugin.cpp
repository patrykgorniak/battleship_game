#include "GameBasePlugin.h"
#include "GameManager.h"
#include <QtDeclarative/qdeclarative.h>
#include <QPair>


void GameBasePlugin::registerTypes(const char *uri)
{
    // @uri com.mycompany.qmlcomponents
    qmlRegisterType<GameManager>(uri, 1, 0, "GameManager");
}

Q_EXPORT_PLUGIN2(GameBasePlugin, GameBasePlugin)

