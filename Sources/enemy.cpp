#include "Enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "game.h"
#include <QList>
#include "Player.h"
#include "Bullet.h"
#include "fragments.h"
#include "musicplayer.h"
#include "Text_manager.h"

extern Game * game;

Enemy::Enemy()  //Constructor - when object is created
{
    int random_x = rand() % 700 + 15;

    int random_type = rand() % 100 + 1;

    if(random_type >= 1 && random_type <= 60)
    {
        type = light;
        QPixmap enemy_img(":/images/enemy_light.png");
        enemy_pix = enemy_img.scaled(QSize(60,60),  Qt::KeepAspectRatio);
        setPos(random_x,-50);
    }
    if(random_type > 60 && random_type <= 90)
    {
        type = medium;
        QPixmap enemy_img(":/images/enemy_medium.png");
        enemy_pix = enemy_img.scaled(QSize(100,100),  Qt::KeepAspectRatio);
        setPos(random_x,-50);
    }
    if(random_type >= 95 && !heavy_active)
    {
        heavy_active = true;
        type = heavy;
        QPixmap enemy_img(":/images/Hard.png");
        enemy_pix = enemy_img.scaled(QSize(600,600),  Qt::KeepAspectRatio);
        setPos(100,-600);

    }

    setPixmap(enemy_pix);


    //přiřadit signal na slot(connect) -- když se něco stane(signal[tady je to timeout]) tak se zavolá nějaká metoda atp(ze slotu)

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}


void Enemy::move()
{
    //move enemy down

    if(type == light)
    {
        setPos(x(),y()+5);
    }

    if(type == medium)
    {
        setPos(x(),y()+2.5);
    }

    if(type == heavy)
    {
        setPos(x(),y()+1);
    }


    QGraphicsItem * player;

    //on collision with player
    QList<QGraphicsItem *> colliding_items = collidingItems();  //vrací array všechn objektů se kterými je enemy v kolizi
    for(int i = 0; i<colliding_items.size(); i++)
    {
        if(typeid(*(colliding_items[i])) == typeid(Player))
        {
            player = colliding_items[i];

            if(type==heavy)
            {
                for(int i=0;i<10;i++)
                {
                    Fragments * frags = new Fragments(player, true, true,true);
                    scene() -> addItem(frags);
                }
                Health=0;
                mp->Play_sound(mp->yolo_sound);
                player->setScale(0);
                player->setPos(-1000000,100000);    //problem solvin IQ 300
                game->health_text->change_text("Health: ",0);
                Text_manager * yolo_text = new Text_manager("You Lose!",315,270,true);
                player->scene()->addItem(yolo_text);
                QTimer * timer_restart = new QTimer();
                File_manager * file_m = new File_manager();
                file_m->write_file("score.txt", game->score);
                std::string y = file_m->open_file("score.txt");
                connect(timer_restart,SIGNAL(timeout()),this,SLOT(restart()));
                timer_restart->start(4000);
            }


            if(type==light || type==medium)
            {
                Health -= 5;
            if(Health <= 0)
            {
                game->health_text->change_text("Health: ",0);
                for(int i=0;i<25;i++)
                {
                    Fragments * frags = new Fragments(player, true, true,true);
                    scene() -> addItem(frags);
                }
                mp->Play_sound(mp->yolo_sound);
                player->setScale(0);
                player->setPos(-1000000,100000);    //problem solvin IQ 300
                Text_manager * yolo_text = new Text_manager("You Lose!",315,270,true);
                player->scene()->addItem(yolo_text);

                File_manager * file_m = new File_manager();
                file_m->write_file("score.txt", game->score);
                std::string y = file_m->open_file("score.txt");

                QTimer * timer_restart = new QTimer();
                connect(timer_restart,SIGNAL(timeout()),this,SLOT(restart()));
                timer_restart->start(4000);
            }
            else
            {
            game->health_text->change_text("Health: ",Health);
            for(int i=0;i<10;i++)
            {
                Fragments * frags = new Fragments(player,true,false,true);
                scene() -> addItem(frags);
            }
                mp->Play_sound(mp->explosion_sound);

                //smazat ze sceny
                scene() -> removeItem(this);
                //smazat z paměti
                delete this;    //enemy
            }

            }
            return;
        }

        if(typeid(*(colliding_items[i])) == typeid(Bullet))
        {
            delete colliding_items[i];
            if(type == light)
            {
                enemy_HP -=10;
            }

            if(type == medium)
            {
                enemy_HP -=5;
            }

            if(type == heavy)
            {
                enemy_HP -=0.8f;
            }

            if(enemy_HP <= 0)
            {

                if(type==heavy)
                {
                    heavy_active = false;
                    for(int i=0;i<50;i++)
                    {
                        Fragments * frags = new Fragments(this,false,true,true);
                        scene() -> addItem(frags);
                    }
                }else
                {
                for(int i=0;i<10;i++)
                {
                    Fragments * frags = new Fragments(this);
                    scene() -> addItem(frags);
                }
                }

                //MusicPlayer * mp = new MusicPlayer();
                mp->Play_sound(mp->explosion_sound);

                score += rand() % 5 + 1;
                game->score_text->change_text("Score: ",score);
                game->score = score;
                game->best_score_text->change_text("Best Score: ",game->file_m->get_best_score());

                //smazat z paměti
                delete this;    //bullet


            }
            else
            {
                //MusicPlayer * mp = new MusicPlayer();
                mp->Play_sound(mp->hit_sound);
            }
            return;
        }
    }

    if(this->pos().y() > 565)
    {
        if(type==heavy && !i_know)
        {
            player_lost = true;
            i_know = true;
            Health=0;
            mp->Play_sound(mp->yolo_sound);
            game->health_text->change_text("Health: ",0);
            Text_manager * yolo_text = new Text_manager("You Lose!",315,270,true);
            scene()->addItem(yolo_text);
            QTimer * timer_restart = new QTimer();
            connect(timer_restart,SIGNAL(timeout()),this,SLOT(restart()));
            timer_restart->start(4000);
        }


        for(int i=0;i<10;i++)
        {
            Fragments * frags = new Fragments(this, true);
            scene() -> addItem(frags);
        }
        //MusicPlayer * mp = new MusicPlayer();
        //mp->Play_sound(mp->explosion_sound);
        Health -= 10;

        if(Health > 0)
        {
        game->health_text->change_text("Health: ",Health);
        scene()->removeItem(this);  //smaže ze sceny, ale ne samotný objekt
        delete  this;               //smaže samotný objekt
        }
        else if(Health <= 0 && !player_lost)
        {
            player_lost = true;
            mp->Play_sound(mp->yolo_sound);
            game->health_text->change_text("Health: ",0);
            Text_manager * yolo_text = new Text_manager("You Lose!",315,270,true);
            scene()->addItem(yolo_text);
            QTimer * timer_restart = new QTimer();
            connect(timer_restart,SIGNAL(timeout()),this,SLOT(restart()));
            timer_restart->start(4000);

            File_manager * file_m = new File_manager();
            file_m->write_file("score.txt", game->score);
            std::string y = file_m->open_file("score.txt");
        }

        return;
    }

}


