#ifndef FIRE_H
#define FIRE_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QtDebug>
#include <QObject>

class Fire: public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
public:
    QPixmap fire_pix;

    Fire(QGraphicsItem * parent=0, bool left_motor=true)
    {
        if(left_motor)
        {
            setPos(parent->x()+28,parent->y()+80);
        }
        else
        {
            setPos(parent->x()+66,parent->y()+80);
        }

        QPixmap fire_img(":/images/fire.png");
        fire_pix = fire_img.scaled(QSize(6,6),  Qt::IgnoreAspectRatio);
        setPixmap(fire_pix);

        QTimer * timer_fire_remove = new QTimer();
        QObject::connect(timer_fire_remove,SIGNAL(timeout()),this,SLOT(remove_fire()));
        timer_fire_remove->start(200);
    }


public slots:

    void remove_fire()
    {
        //qDebug() << "Removing fire";
        delete this;
        return;
    }


};
#endif // FIRE_H
