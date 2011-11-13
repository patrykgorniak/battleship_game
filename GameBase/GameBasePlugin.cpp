#include "GameBasePlugin.h"
#include <QtDeclarative/qdeclarative.h>

void GameBasePlugin::registerTypes(const char *uri)
{
    // @uri com.mycompany.qmlcomponents
//    qmlRegisterType<>(uri, 1, 0, "MyItem");
}

Q_EXPORT_PLUGIN2(GameBase, GameBasePlugin)

