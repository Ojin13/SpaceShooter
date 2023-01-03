#include "Player.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <Enemy.h>
#include <Star.h>
#include <windows.h>
#include "game.h"
#include "Fire.h"
#include "File_manager.h";
#include "musicplayer.h"

extern Game * game;

void Player::keyPressEvent(QKeyEvent *event)
{

    //vypnout
    if(event->key() == Qt::Key_X)
    {
        File_manager * file_m = new File_manager();
        file_m->write_file("score.txt", game->score);
        std::string y = file_m->open_file("score.txt");
        QCoreApplication::quit();
    }


    //movement
    if(event->key() == Qt::Key_Left)
    {
        go_left = true;
    }

    if(event->key() == Qt::Key_Right)
    {
        go_right = true;
    }

    if(event->key() == Qt::Key_Up)
    {
        go_up = true;
    }

    if(event->key() == Qt::Key_Down)
    {
        go_down = true;
    }

    if(event->key() == Qt::Key_A)
    {
        go_left = true;
    }

    if(event->key() == Qt::Key_D)
    {
        go_right = true;
    }

    if(event->key() == Qt::Key_W)
    {
        go_up = true;
    }

    if(event->key() == Qt::Key_S)
    {
        go_down = true;
    }

    //shooting
    if(event->key() == Qt::Key_Space)
    {
        shooting = true;
    }


}



void Player::keyReleaseEvent(QKeyEvent *event)
{
    //movement
    if(event->key() == Qt::Key_Left)
    {
        go_left = false;
    }

    if(event->key() == Qt::Key_Right)
    {
        go_right = false;
    }

    if(event->key() == Qt::Key_Up)
    {
        go_up = false;
    }

    if(event->key() == Qt::Key_Down)
    {
        go_down = false;
    }

    if(event->key() == Qt::Key_A)
    {
        go_left = false;
    }

    if(event->key() == Qt::Key_D)
    {
        go_right = false;
    }

    if(event->key() == Qt::Key_W)
    {
        go_up = false;
    }

    if(event->key() == Qt::Key_S)
    {
        go_down = false;
    }

    //shooting
    if(event->key() == Qt::Key_Space)
    {
        shooting = false;
    }

}



void Player::movement()
{

    //Pokud uživatel klikne do jiného okna Player přestane vnímar signály z klávesnice - musí se restartovat focus!
    this->setFocus();

    if(go_down || go_up || go_left || go_right)
    {
    Fire * fire_l = new Fire(this, true);
    Fire * fire_r = new Fire(this, false);
    scene() -> addItem(fire_l);
    scene() -> addItem(fire_r);
    }

    //movement

    if(go_down)
    {
        if(this->pos().y()+player_img.height()< 600)
        {
        setPos(x(),y()+speed);
        }
    }

    if(go_left)
    {
        if(this->pos().x() > 0)
        {
        setPos(x() - speed,y());
        }
    }

    if(go_right)
    {
        if(this->pos().x()+player_img.width() < scene()->width())
        {
        setPos(x() + speed,y());
        }
    }

    if(go_up)
    {
        if(this->pos().y() > 0)
        {
        setPos(x(),y()-speed);
        }
    }

}

void Player::shoot()
{
    if(shooting)
    {
            Bullet * bullet = new Bullet();
            bullet->setPos(x()+player_img.width()/2-bullet->bullet_pix.width()/2,y()-bullet->bullet_pix.height());
            scene()->addItem(bullet);

            //MusicPlayer * mp = new MusicPlayer();
            mpl->Play_sound(mpl->bullet_sound);

            if(this->pos().y()+player_img.height() < 600)
            {
            setPos(x(),y()+speed);
            }


    }
}

void Player::spawn_stars()
{
        //player
        Star * star = new Star();
        scene()->addItem(star);
}

void Player::how_to_play()
{
    if(fm->open_file("tutorial_shown").find("1") == std::string::npos)
    {
        UI_initialized = true;
        fm->write_file("tutorial_shown",1);
        game->setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
        QThread::msleep(5000);
        scene()->addItem(game->score_text);
        scene()->addItem(game->health_text);
        scene()->addItem(game->best_score_text);
    }
    else
    {
        if(!UI_initialized)
        {
        UI_initialized = true;
        game->setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
        scene()->addItem(game->score_text);
        scene()->addItem(game->health_text);
        scene()->addItem(game->best_score_text);
        }
    }
}


void Player::spawn()
{
    //Create enemy
        Enemy * enemy = new Enemy();
        scene() -> addItem(enemy);

        //File_manager * file_m = new File_manager();
       // file_m->write_file("score.txt", enemy->pos().x());
}
