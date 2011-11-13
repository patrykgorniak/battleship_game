TARGET=demo
TEMPLATE= app
QT+= core

SOURCES+=main.cpp
INCLUDEPATH+= ../GameBase
LIBS=-L ../GameBase -lGameBase
