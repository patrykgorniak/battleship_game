TARGET=GameManager
TEMPLATE=lib
QT += declarative
CONFIG += qt plugin


TARGET = $$qtLibraryTarget($$TARGET)
uri = com.mycompany.qmlcomponents

HEADERS+= $$PWD/GameBase.h \
    $$PWD/GameBoard.h \
    $$PWD/Ship.h \
    $$PWD/GameBasePlugin.h \
    $$PWD/GameManager.h \
    $$PWD/GameHistogram.h \
    $$PWD/ShotGenerator.h \
    $$PWD/Common.h \
    BoardGenerator.h

SOURCES+= $$PWD/GameBoard.cpp \
    $$PWD/Ship.cpp \
    $$PWD/GameBasePlugin.cpp \
    $$PWD/GameManager.cpp \
    $$PWD/GameHistogram.cpp \
    $$PWD/ShotGenerator.cpp \
    $$PWD/Common.cpp \
    BoardGenerator.cpp


