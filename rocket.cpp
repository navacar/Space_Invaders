#include "rocket.h"
#include "mainwindow.h"
#include <QPainter>
#include <QRect>
#include <QDebug>
Rocket::Rocket()
      :Rocket(0,0)
{

}

Rocket::Rocket(int ShipRocketX, int ShipRocketY){


    ShipBomb = QImage(":/ABC/images/Bomba.jpg");
    this -> ShipRocketX = ShipRocketX;
    this -> ShipRocketY = ShipRocketY;

}

int Rocket::moveRocket()
{
    ShipRocketY -= 10;
    return  ShipRocketY;
}

void Rocket::Draw(QPainter *painter)
{
    painter -> drawImage(QRect(ShipRocketX + RocketWeight/2, ShipRocketY, RocketHeight, RocketWeight), ShipBomb);
}

int Rocket::getX()
{
    return ShipRocketX;
}

int Rocket::getY()
{
    return ShipRocketY;
}

int Rocket::getHeight()
{
    return RocketHeight;
}

int Rocket::getWeight()
{
    return RocketWeight;
}
