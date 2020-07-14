#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Rocket;
class alien;
class alienRocket;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    bool HitBox(Rocket *rocket, alien *alien);
    bool HitBox1(Rocket *rocket, alienRocket * alienrocket);
    bool HitBox2(alienRocket *alienrocket);


public slots:
   void update();

private:
    Ui::MainWindow *ui;
    QImage Ship;
    int i, j, ShipX, Trigger, TriggerForAlien, RocketX, xBorder, yBorder, HP, Score;
    int AlienX[7], AlienY[4], NewAlienX[7][4];
    const int ShipY = 525, ShipHeight = 40, ShipWeight = 40;
    Rocket * BigRocket;
    alien * BigAlien[7][4];
    alienRocket * BigAlienRocket;
};
#endif // MAINWINDOW_H
