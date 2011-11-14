#include "GameManager.h"


GameManager::GameManager(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    m_board = new Base::GameBoard(10);
}

QList<int> GameManager::readEnemyBoard()
{

}

QList<int> GameManager::readBoard()
{

}

GameManager::~GameManager()
{

}
