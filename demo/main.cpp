#include <QApplication>
#include <GameBase.h>
#include <Ship.h>
#include <iostream>


using namespace std;
using namespace Base;

int main(int argc, char** argv)
{
  cout<<"Before game call"<<endl;
  GameBoard game;
  game.savePlayerMoveResult(5,5,game.validateMove(5,5));
  cout<<game<<endl;
//  Ship ship(Ship::AIRCRAFT_CARRIER,Ship::RIGHT);
//  ship.setPosition(10,10);
//  Ship ship2(Ship::PATROL_BOAT,Ship::UP);
//  ship2.setPosition(9,8);
//  cout << "Ship 1: "<<game.addShip(ship) << endl;
//  cout << "Ship 2: "<<game.addShip(ship2)<< endl;
//  cout<< "Validate Move: "<<game.validateMove(9,8)<<endl;
//  cout<< "Validate Move: "<<game.validateMove(10,10)<<endl;
//  cout<< "Validate Move: "<<game.validateMove(10,11)<<endl;
//  cout<< "Validate Move: "<<game.validateMove(10,12)<<endl;
//  cout<< "Validate Move: "<<game.validateMove(10,13)<<endl;
//  cout<< "Validate Move: "<<game.validateMove(10,14)<<endl;
//  cout<<game<<endl;
//  cout<<"After game call"<<endl;
  return 0;
}
