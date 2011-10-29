#include <QApplication>
#include "GameBase.h"
#include <iostream>
#include <Ship.h>

using namespace std;
using namespace Base;

int main(int argc, char** argv)
{
  cout<<"Before game call"<<endl;
  GameBoard game(15);
  cout<<game<<endl;
  Ship ship(Ship::AIRCRAFT_CARRIER,Ship::RIGHT);
  ship.setPosition(10,10);
  Ship ship2(Ship::BATTLESHIP,Ship::UP);
  ship2.setPosition(9,8);
  cout << "Ship 1: "<<game.addShip(ship) << endl;
  cout << "Ship 2: "<<game.addShip(ship2)<< endl;
  cout<<game<<endl;
  cout<<"After game call"<<endl;
  return 0;
}
