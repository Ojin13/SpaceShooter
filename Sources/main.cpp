#include <QApplication>
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <File_manager.h>
#include <QDebug>

//Globální objekt Game - scena a rezvětvení
Game * game;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    game = new Game();  //vytvoření objektu
    game->show();   //Zobrazení scény

    srand (time(0));    //Pokud se zavolá vícekrát tak to nefunguje!!!

    return a.exec();
}
