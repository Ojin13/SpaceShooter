#ifndef FRAGMENTS_H
#define FRAGMENTS_H


#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QtDebug>
#include <QObject>
#include <Player.h>

class Fragments: public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
public:
    QPixmap fragment_pix;
    int random_x_direction = ((float(rand()) / float(RAND_MAX)) * (10 - -10)) + -10;
    int random_y_direction = ((float(rand()) / float(RAND_MAX)) * (10 - -10)) + -10;

    Fragments(QGraphicsItem * parent=0, bool is_player=false, bool yolo=false, bool yellow=false)
    {
        if(!is_player)
        {
        setPos(parent->x()+parent->boundingRect().width()/2,parent->y()+parent->boundingRect().height()/2);
        }
        else
        {
            setPos(parent->x()+50,parent->y()+50);
        }

        if(yellow)
        {
            QPixmap fragment_img(":/images/yellow.png");
            fragment_pix = fragment_img.scaled(QSize(6,6),  Qt::IgnoreAspectRatio);
        }
        else
        {
            QPixmap fragment_img(":/images/white.png");
            fragment_pix = fragment_img.scaled(QSize(6,6),  Qt::IgnoreAspectRatio);
        }

        setPixmap(fragment_pix);

        QTimer * timer_fragment_remove = new QTimer();
        QObject::connect(timer_fragment_remove,SIGNAL(timeout()),this,SLOT(remove_fragment()));

        if(yolo)
        {
            timer_fragment_remove->start(5000);
        }
        else
        {
            timer_fragment_remove->start(500);
        }

        QTimer * timer_fragment_move = new QTimer();
        QObject::connect(timer_fragment_move,SIGNAL(timeout()),this,SLOT(move_fragment()));
        timer_fragment_move->start(50);
    }


public slots:

    void remove_fragment()
    {
        //qDebug() << "Removing fragment";
        scene() -> removeItem(this);
        delete this;
        return;
    }

    void move_fragment()
    {
        setPos(x()+random_x_direction,y()+random_y_direction);
    }


};


#endif // FRAGMENTS_H
