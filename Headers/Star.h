#ifndef STAR_H
#define STAR_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QtDebug>
#include <QThread>

class Star: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    QPixmap Star_pix;
    int random_speed;
    float star_lenght=1;
    Star()
    {
        random_speed = rand() % 10 + 1;
        int random_x = rand() % 785 + 15;
        setPos(random_x,0);
        //drew the rect
        QPixmap enemy_img(":/images/white.png");
        Star_pix = enemy_img.scaled(QSize(1,1),  Qt::IgnoreAspectRatio);
        setPixmap(Star_pix);
        //přiřadit signal na slot(connect) -- když se něco stane(signal[tady je to timeout]) tak se zavolá nějaká metoda atp(ze slotu)
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move_star()));
        timer->start(50);
    }



public slots:

    void move_star()
    {

        //star_lenght += star_lenght / 5;
        setPos(x(),y()+ random_speed);
        QPixmap enemy_img(":/images/white.png");
        Star_pix = enemy_img.scaled(QSize(1,star_lenght),  Qt::IgnoreAspectRatio);
        setPixmap(Star_pix);
        if(this->pos().y() > 600)
        {
            scene()->removeItem(this);  //smaže ze sceny, ale ne samotný objekt
            delete  this;               //smaže samotný objekt
            return;
        }
    }

};
#endif // STAR_H
