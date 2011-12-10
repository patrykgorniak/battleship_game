#include "GameManager.h"
#include <iostream>

GameManager::GameManager(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    srand(time(NULL));
    m_board = new Base::GameBoard();
    m_board->setObjectName("board");
    qDebug()<<"Your board: \n"<<m_board->readBoard();

    m_enemyBoard = new Base::GameBoard();
    m_enemyBoard->setObjectName("enemyBoard");
    qDebug()<<"Enemy board: \n"<<m_enemyBoard->readBoard();
    m_enemyBoard->generateBoard();
    connect(m_board,SIGNAL(boardChanged()),this,SIGNAL(dataChanged()));
    connect(m_enemyBoard,SIGNAL(shipDestroyed()),this,SIGNAL(shipDestroyed()));
    connect(m_board,SIGNAL(shipDestroyed()),this,SIGNAL(shipDestroyed()));
    connect(m_board,SIGNAL(gameFinished()),this,SIGNAL(gameFinished()));
    connect(m_enemyBoard,SIGNAL(gameFinished()),this,SIGNAL(gameFinished()));
}

void GameManager::generateBoard()
{
    m_board->generateBoard();
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
//    qDebug()<<"I catched shot in plugin at field nb: "<<fieldNb;
//    qDebug()<<m_enemyBoard->readBoard();
    Base::GameBoard::MoveResult res = m_enemyBoard->makeShot(fieldNb);
    if(res!=Base::GameBoard::INCORRECT_COORDINATES)
    {
        m_board->savePlayerMoveResult(fieldNb,res);
        int randShot = m_enemyBoard->getRandomShot();
        m_enemyBoard->savePlayerMoveResult(randShot,m_board->makeShot(randShot));
    }
    else
    {
        qDebug()<<"Incorrect shot. Try again";
    }
    m_board->print(std::cout);
    m_enemyBoard->print(std::cout);
}

GameManager::~GameManager()
{
    delete m_board;
}

void GameManager::shotNotify()
{
    qDebug()<<"SHOT";
}

int GameManager::addShip(int sails)
{
    return m_board->addShip(sails);
}

int GameManager::removeShip(int shipID)
{
    return m_board->removeShipById(shipID);
}

bool GameManager::moveShip(int id,int x,int y)
{
    return m_board->moveShip(id,x,y);
}

bool GameManager::validateShipPosition(int id, int x, int y)
{
    return m_board->validateShipPosition(id,x,y);
}

bool GameManager::rotateShip(int id, bool direction)
{
    return m_board->rotateShip(id,direction);
}

bool GameManager::validateRotation(int id, bool direction)
{
    return m_board->validateRotation(id,direction);
}
