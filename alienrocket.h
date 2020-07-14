#ifndef ALIENROCKET_H
#define ALIENROCKET_H
#include <QPainter>
#include <QImage>

class alienRocket
{
public:
    alienRocket();
    alienRocket(int AlienRocketX, int AlienRocketY);
    int moveAlienRocket();
    void Draw(QPainter *painter);
    int getX();
    int getY();
    int getHeight();
    int getWeight();

private:
    int AlienRocketX, AlienRocketY;
    QImage AR;
    const int AlienRocketWeight = 30, AlienRocketHeight = 10;

};

#endif // ALIENROCKET_H
