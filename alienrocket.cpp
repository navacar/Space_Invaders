#include "alienrocket.h"
#include <QPainter>
#include<QRect>


alienRocket::alienRocket()
{

}

alienRocket::alienRocket(int AlienRocketX, int AlienRocketY)
{
    this -> AlienRocketX = AlienRocketX;
    this -> AlienRocketY = AlienRocketY;

    AR = QImage(":/ABC/images/BombaAlien.jpg");
}

int alienRocket::moveAlienRocket()
{
    AlienRocketY += 5;
    return AlienRocketY;
}

void alienRocket::Draw(QPainter *painter)
{
    painter->drawImage(QRect(AlienRocketX, AlienRocketY, AlienRocketHeight, AlienRocketWeight), AR);
}

int alienRocket::getX()
{
    return AlienRocketX;
}

int alienRocket::getY()
{
    return AlienRocketY;
}

int alienRocket::getHeight()
{
    return AlienRocketHeight;
}

int alienRocket::getWeight()
{
    return AlienRocketWeight;
}
