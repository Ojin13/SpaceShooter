#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H



#include <QMediaPlayer>
#include <windows.h>
#include <qdebug.h>

class MusicPlayer
{
public:

    QMediaPlayer * explosion_sound;
    QMediaPlayer * bullet_sound;
    QMediaPlayer * yolo_sound;
    QMediaPlayer * hit_sound;

    MusicPlayer()
    {
        explosion_sound = new QMediaPlayer();
        explosion_sound->setMedia(QUrl("qrc:/sounds/explosion.wav"));

        bullet_sound = new QMediaPlayer();
        bullet_sound->setMedia(QUrl("qrc:/sounds/shoot.wav"));

        yolo_sound = new QMediaPlayer();
        yolo_sound->setMedia(QUrl("qrc:/sounds/you_lose.wav"));

        hit_sound = new QMediaPlayer();
        hit_sound->setMedia(QUrl("qrc:/sounds/hit.wav"));
    }
    void Play_sound(QMediaPlayer * sound)
    {
        if(sound->state() == QMediaPlayer::PlayingState)
        {
            sound->setPosition(0);
        }
        else if(sound->state() == QMediaPlayer::StoppedState)
        {
            sound->play();
            //delete this;
        }

    }
};



#endif // MUSICPLAYER_H
