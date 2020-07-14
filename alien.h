#ifndef ALIEN_H
#define ALIEN_H
#include <QPaintEvent>
#include <QPainter>

class alien
{
public:
    alien();
    alien(int AlienX, int AlienY);
    int moveAlien(int xBorder);
    void Draw(QPainter *painter);
    int getX();
    int getY();
    int getHeight();
    int getWeight();

private:
    QImage Alien;
    int AlienX, AlienY, Right, count;
    static int AlienHeight, AlienWeight;
};

#endif // ALIEN_H
