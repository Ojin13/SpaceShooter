#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject> //musím includovat pokud pracuji se sloty
#include <File_manager.h>
#include <musicplayer.h>


static int Health = 100;
static float speed = 8;
static bool is_alive = true;

class Player:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:


    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    bool go_left = false;
    bool go_right = false;
    bool go_up = false;
    bool go_down = false;
    bool shooting = false;
    bool UI_initialized = false;
    File_manager * fm = new File_manager();
    MusicPlayer * mpl= new MusicPlayer();

    QPixmap player_img;
    void get_player_size(QPixmap size){
        player_img = size;
    }

public slots:
    void spawn();
    void movement();
    void shoot();
    void spawn_stars();
    void how_to_play();
};

static Player * player_obj;
#endif // PLAYER_H
