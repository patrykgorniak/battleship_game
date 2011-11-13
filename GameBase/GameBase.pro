TARGET=GameBase
TEMPLATE=lib
QT += declarative
CONFIG += qt plugin


HEADERS+= $$PWD/GameBase.h \
    $$PWD/GameBoard.h \
    $$PWD/Ship.h \
    GameBasePlugin.h

SOURCES+= $$PWD/GameBoard.cpp \
    $$PWD/Ship.cpp \
    GameBasePlugin.cpp






