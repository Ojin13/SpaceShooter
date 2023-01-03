#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include <QGraphicsTextItem>
#include <QFont>
#include <string>
#include <QDebug>
#include <QGraphicsScene>

static int score = 0;

class Text_manager: public QGraphicsTextItem{

public:
    bool score_started = false;
    Text_manager(std::string text, int PosX, int PosY, bool red_color=false){
        // draw the text
        QString Q_text = QString::fromStdString(text);
        setPlainText(Q_text);
        if(red_color)
        {
            setDefaultTextColor(Qt::red);
            setFont(QFont("times",35));
        }
        else
        {
            setFont(QFont("times",16));
            setDefaultTextColor(Qt::white);
        }

        setPos(PosX,PosY);

    }

    void change_text(std::string text, int value)
    {
        QString text_of_value = QString::fromStdString(text);

        /*if (text.find("Score") != std::string::npos)
        {
        score = value;
        }
        */

        setPlainText(text_of_value + QString::number(value));
    }
};


#endif // TEXT_MANAGER_H
