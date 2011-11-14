#include "GameManager.h"


GameManager::GameManager(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    m_board = new Base::GameBoard(10);
}

QList<int> GameManager::readEnemyBoard()
{
    return m_board->readEnemyBoard();
}

QList<int> GameManager::readBoard()
{
    return m_board->readBoard();
}

void GameManager::shot(int fieldNb)
{
    qDebug()<<fieldNb;
}

GameManager::~GameManager()
{
    delete m_board;
}
