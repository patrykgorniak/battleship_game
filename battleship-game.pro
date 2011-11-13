TEMPLATE= subdirs
SUBDIRS += GameManager demo
CONFIG+=ordered

OTHER_FILES += QML/*.qml \
    QML/content/*.qml \
    QML/content/BoardConfigurator/*.qml \
    QML/content/GameBoard/*.qml \
    QML/content/Ships/*.qml
