#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "Text_manager.h"
#include "File_manager.h"

class Game: public QGraphicsView{

public:

    Game(QWidget * parent=0);
    QGraphicsScene * scene;
    Text_manager * score_text;
    Text_manager * health_text;
    Text_manager * best_score_text;
    QPixmap player_pix;
    File_manager * file_m = new File_manager();
    int score = 0;

};

#endif // GAME_H
