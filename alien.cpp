#include "alien.h"
#include "mainwindow.h"
#include <QPainter>
#include <QRect>
#include <QDebug>

int alien::AlienHeight = 30;
int alien::AlienWeight = 30;
alien::alien()
     :alien(0,0)
{

}
alien::alien(int AlienX, int AlienY){
    Alien = QImage(":/ABC/images/alien.bmp");
    this -> AlienX = AlienX;
    this -> AlienY = AlienY;
    Right = 1;
    count = 0;

}
int alien::moveAlien(int xBorder)
{

    if (count == 1 && Right == 1){
        count = 0;
        Right = 0;
        AlienY += 30;
    }

    if (count == 1 && Right == 0){
        count = 0;
        Right = 1;
        AlienY += 30;
    }

    if (Right == 1){
        if (AlienX < xBorder-75){
            AlienX += 1;
        }else{
            count += 1;
        }
    }

    if (Right == 0){
        if (AlienX > 25){
            AlienX -= 1;
        }else{
            count += 1;
        }
    }
    return AlienX;
}

void alien::Draw(QPainter *painter)
{
    painter->drawImage(QRect(AlienX, AlienY, 30 , 30), Alien);
}

int alien::getX()
{
    return AlienX;
}

int alien::getY()
{
    return AlienY;
}

int alien::getHeight()
{
    return AlienHeight;
}

int alien::getWeight()
{
    return AlienWeight;
}
