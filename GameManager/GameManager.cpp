#include "GameManager.h"


GameManager::GameManager(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    m_board = new Base::GameBoard(10);

    connect(this,SIGNAL(dataChanged()),m_board,SIGNAL(boardChanged()));
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
    qDebug()<<"I catched shot in plugin at field nb: "<<fieldNb;
    m_board->makeShot(fieldNb);
}

GameManager::~GameManager()
{
    delete m_board;
}
