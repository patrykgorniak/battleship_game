TARGET=GameBase
TEMPLATE=lib 
CONFIG+=dll


HEADERS+= $$PWD/GameBase.h \
    $$PWD/GameBoard.h \
    $$PWD/Ship.h

SOURCES+= $$PWD/GameBoard.cpp \
    $$PWD/Ship.cpp
