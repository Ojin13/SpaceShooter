#include "game.h"
#include <QGraphicsItem>
#include <QFont>
#include <QTimer>
#include "Enemy.h"
#include "Star.h"
#include "Text_manager.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>

    Game::Game(QWidget *parent){

    //create scene -- není okno ale to ce je v něm
    QGraphicsScene * scene = new QGraphicsScene();
    setScene(scene);
    //setup scene background-image
    if(file_m->open_file("tutorial_shown").find("1") == std::string::npos)
    {
        setBackgroundBrush(QBrush(QImage(":/images/Tutorial.png")));
    }
    else
    {
        setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
    }
    //add view(to display scene) -- samotné okno
    QGraphicsView * view = new QGraphicsView(scene);
    //vypnout scrollbar x/y
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowTitle("Klauzury SpaceShooter");

    //zobrazit scenu...
   // view->show(); ------------------------------------------
    //nastavit velikost okna v px
    this->setFixedSize(800,600);
    //nastavit fixnutou velikost sceny
    scene->setSceneRect(0,0,800,600);

    Player * player = new Player();

    QTimer * timer_bg = new QTimer();
    QObject::connect(timer_bg,SIGNAL(timeout()),player,SLOT(how_to_play()));
    timer_bg->start(1000);


    player_obj = player;
    //(pozice x, pozice y, x px, y px) --- pozice 0,0 je střed..
    QPixmap player_img(":/images/player.png");
    player_pix = player_img.scaled(QSize(100,100),  Qt::IgnoreAspectRatio);
    player->setPixmap(player_pix);
    //make rect focusable - detekuje input klavesnice
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    Qt::WindowFlags flags = this->windowFlags(); this->setWindowFlags(flags|Qt::FramelessWindowHint);
    player->setFocus();
    player->setPos(this->width()/2-player_pix.width()/2,this->height()/2-player_pix.height()/2);
    player->get_player_size(player_pix);
    //add rect to scene
    scene->addItem(player);

    // create texts
     score_text = new Text_manager("Score: 0",0,0);
     health_text = new Text_manager("Health: 100",scene->width()/2,0);
     best_score_text = new Text_manager("Best Score: ",0,30);
     best_score_text->change_text("Best Score: ",file_m->get_best_score());

    //Spanw enemies
    QTimer * timer_spawn = new QTimer();
    QTimer * timer_movement = new QTimer();
    QTimer * timer_shoot = new QTimer();
    QTimer * timer_stars = new QTimer();

    QObject::connect(timer_spawn,SIGNAL(timeout()),player,SLOT(spawn()));
    QObject::connect(timer_movement,SIGNAL(timeout()),player,SLOT(movement()));
    QObject::connect(timer_shoot,SIGNAL(timeout()),player,SLOT(shoot()));
    QObject::connect(timer_stars,SIGNAL(timeout()),player,SLOT(spawn_stars()));

    timer_spawn->start(2000);
    timer_shoot->start(400);
    timer_movement->start(50);
    timer_stars->start(500);

    //play background music - nakonec není
    QMediaPlayer * bg_music_player = new QMediaPlayer();
    bg_music_player->setMedia(QUrl("qrc:/sounds/bg.wav"));
    bg_music_player->play();

    }



