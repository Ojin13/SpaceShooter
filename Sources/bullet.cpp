#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "Game.h"
#include <stdlib.h>
#include "Text_manager.h"
#include "fragments.h"
#include "musicplayer.h"

extern Game * game; // there is an external global object called game


Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{


    QPixmap bullet_img(":/images/bullet.png");
    bullet_pix = bullet_img.scaled(QSize(15,15),  Qt::KeepAspectRatio);
    setPixmap(bullet_pix);


    //přiřadit signal na slot(connect) -- když se něco stane(signal[tady je to timeout]) tak se zavolá nějaká metoda atp(ze slotu)

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Bullet::move()
{

    //move bullet up
    setPos(x(),y()-10);

    if(this->pos().y() < 0)
    {
        scene()->removeItem(this);
        delete  this;
        qDebug() <<"Bullet destroyed";
    }
}

