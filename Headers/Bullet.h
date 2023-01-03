#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>  //musím includovat když používám slots and signals
#include <game.h>


class Bullet: public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent=0);   //konstruktor
    QPixmap bullet_pix;



public slots:
    void move();
};


#endif // BULLET_H
