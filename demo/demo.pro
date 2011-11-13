TARGET=demo
TEMPLATE= app
QT+= core

SOURCES+=main.cpp
INCLUDEPATH+= ../GameManager
LIBS=-L ../GameManager -lGameManager
