#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rocket.h"
#include "alien.h"
#include "alienrocket.h"
#include <QPainter>
#include <QKeyEvent>
#include <QRect>
#include <QPaintEvent>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Ship = QImage(":/ABC/images/ship.bmp");
    ShipX = 400;
    AlienX[0] = 25;
    Trigger = 0;
    TriggerForAlien = 0;
    RocketX = 0;
    HP = 5;
    Score = 0;

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(40); // DEFAULT 40

    for(i = 0; i < 7; i++){
        AlienY[0] = 35;
        for(j = 0; j < 4; j++){
            BigAlien[i][j] = new alien(AlienX[i], AlienY[j]);
                AlienY[j+1] = AlienY[j] + 35;
        }
            AlienX[i+1] = AlienX[i] + 35;
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        ShipX=ShipX-50;
    }
    if (event->key() == Qt::Key_Right){
        ShipX=ShipX+50;
    }
    if (event->key() == Qt::Key_Space){
       RocketX = ShipX+15;

        if (Trigger == 0){
            BigRocket = new Rocket(ShipX, ShipY);
            if(BigRocket!=nullptr){
                Trigger = 1;
            }
        }
    }
    repaint();

}

void MainWindow::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QString NumberOfHealth = QString("Число жизней: %1").arg(HP);
    QString ScoreString = QString("Счёт: %1").arg(Score);

    painter.setFont(QFont("Arial",25));
    painter.drawText(10,30, NumberOfHealth);
    painter.drawText(665,30, ScoreString);
    painter.drawImage(QRect(ShipX, ShipY, ShipHeight, ShipWeight), Ship);

    if(BigRocket != nullptr){
        BigRocket->Draw(&painter);
    }

    if(BigAlienRocket != nullptr){
        BigAlienRocket->Draw(&painter);
    }

    for (i = 0; i < 7; i++){
        for (j = 0; j < 4; j++){
            if (BigAlien[i][j]!=nullptr){
                //qDebug("1r");
                BigAlien[i][j]->Draw(&painter);
            }
        }
    }
}

void MainWindow::update()
{
    QRect rect = contentsRect();
    xBorder = rect.width();
    yBorder = rect.height();
    int ShipRocketY = 0, AlienRocketY;
    if (ShipX>xBorder){
        ShipX=0;
    }
    if (ShipX<0){
        ShipX=xBorder;
    }

    if (BigRocket != nullptr)
    {
        ShipRocketY = BigRocket -> moveRocket();
        if(ShipRocketY < -100){
            delete BigRocket;
            BigRocket = nullptr;
            Trigger = 0;
        }
    }
/////////////////////////////
    if (BigAlienRocket == nullptr){
        if (TriggerForAlien == 0){
            i = rand()%7;
            j = 3;

                if (BigAlien[i][j] != nullptr){
                BigAlienRocket = new alienRocket(BigAlien[i][j]->getX(),BigAlien[i][j]->getY());
                TriggerForAlien = 1;
            }else{
                    while(BigAlien[i][j] == nullptr && j >= 0){
                        j--;
                    }

                    if(BigAlien[i][j] != nullptr){
                        BigAlienRocket = new alienRocket(BigAlien[i][j]->getX(),BigAlien[i][j]->getY());
                        TriggerForAlien = 1;
                        j = 3;
                    }
                }
        }
    }
////////////////////////////
    if (BigAlienRocket != nullptr){
        if (TriggerForAlien == 1){
            AlienRocketY = BigAlienRocket->moveAlienRocket();
            if (AlienRocketY > xBorder){
                TriggerForAlien = 0;
                delete BigAlienRocket;
                BigAlienRocket = nullptr;
            }
        }
    }

    if (BigAlienRocket != nullptr && BigRocket != nullptr){
        if (HitBox1(BigRocket, BigAlienRocket) == true && TriggerForAlien == 1){
            delete BigRocket;
            BigRocket = nullptr;
            delete BigAlienRocket;
            BigAlienRocket = nullptr;

            TriggerForAlien = 0;
            Trigger = 0;
        }
    }

    if (BigAlienRocket != nullptr){
        if (HitBox2(BigAlienRocket) && TriggerForAlien == 1){
            delete BigAlienRocket;
            BigAlienRocket = nullptr;

            TriggerForAlien = 0;
            HP--;
        }
    }


    for (i = 0; i < 7; i++){
            for (j = 0; j < 4; j++){
                if (BigAlien[i][j] != nullptr){
                    NewAlienX[i][j] = BigAlien[i][j] -> moveAlien(xBorder);
                }
                if (BigAlien[i][j] != nullptr && BigRocket != nullptr){
                     if (HitBox(BigRocket, BigAlien[i][j]) == true && Trigger == 1)
                     {
                        Score += 500;
                        delete BigRocket;
                        BigRocket = nullptr;
                        Trigger = 0;
                        delete BigAlien[i][j];
                        BigAlien[i][j] = nullptr;
                     }
                }
            }
    }


    if(HP == 0){
        QMessageBox::information(this, "ABC", "Game Over");
        QApplication::exit();

    }

    repaint();
}

bool MainWindow::HitBox(Rocket *rocket, alien *alien)
{
    if (rocket -> getX() + rocket -> getWeight() < alien -> getX() || rocket -> getX() > alien -> getX() + alien -> getHeight() || rocket -> getY() + rocket -> getHeight() < alien -> getY() || rocket -> getY() > alien -> getY() + alien -> getWeight())
        return false;
    else
        return true;
}

bool MainWindow::HitBox1(Rocket *rocket, alienRocket *alienrocket)
{
    if (rocket -> getX() + rocket -> getWeight() < alienrocket -> getX() || rocket -> getX() > alienrocket -> getX() + alienrocket -> getHeight() || rocket -> getY() + rocket -> getHeight() < alienrocket -> getY() || rocket -> getY() > alienrocket -> getY() + alienrocket -> getWeight())
        return false;
    else
        return true;
}

bool MainWindow::HitBox2(alienRocket *alienrocket)
{
    if (ShipX + ShipWeight < alienrocket -> getX() || ShipX > alienrocket -> getX() + alienrocket -> getHeight() || ShipY + ShipHeight < alienrocket -> getY() || ShipY > alienrocket -> getY() + alienrocket -> getWeight())
        return false;
    else
        return true;
}
