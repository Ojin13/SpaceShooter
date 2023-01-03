#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QObject>
#include <QApplication>
#include <QProcess>
#include <musicplayer.h>


static bool heavy_active = false;
static bool player_lost = false;
class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bool i_know = false;
    enum enemy_types
    {
        light,
        medium,
        heavy
    };

    enemy_types type;

    Enemy();    //konstruktor
    QPixmap enemy_pix;
    MusicPlayer * mp = new MusicPlayer();
    float enemy_HP = 10;




    void die();

public slots:
    void move();
    void restart()
    {
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
};
#endif // ENEMY_H
