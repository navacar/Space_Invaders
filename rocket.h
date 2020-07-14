#ifndef ROCKET_H
#define ROCKET_H
#include <QMainWindow>
class QPainter;
class Rocket
{
public:
    Rocket();
    Rocket(int ShipBombY, int ShipBompX);
    int moveRocket();
    void Draw(QPainter *painter);
    int getX();
    int getY();
    int getHeight();
    int getWeight();
private:
    int  ShipRocketY, ShipRocketX, xBorder, yBorder;
    QImage ShipBomb;
    const int RocketWeight = 30, RocketHeight = 10;
};

#endif // ROCKET_H
