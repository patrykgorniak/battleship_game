#include "GameManager.h"


GameManager::GameManager(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    m_board = new Base::GameBoard();
    m_enemyBoard = new Base::GameBoard();

    connect(m_board,SIGNAL(boardChanged()),this,SIGNAL(dataChanged()));
    connect(m_enemyBoard,SIGNAL(shipDestroyed()),this,SIGNAL(shipDestroyed()));
    connect(m_enemyBoard,SIGNAL(gameFinished()),this,SIGNAL(gameFinished()));
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
    m_board->savePlayerMoveResult(fieldNb,m_enemyBoard->makeShot(fieldNb));
}

GameManager::~GameManager()
{
    delete m_board;
}

void GameManager::shotNotify()
{
    qDebug()<<"SHOT";
}
