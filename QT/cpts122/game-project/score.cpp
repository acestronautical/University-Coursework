/* Project: Java Defender (Andy's Face In Space Defending the Base)
 * Programmers: Arrin Bevers, Kiernan, Ace Cassidy, Garrick Hutcheson
 * Date: 12/6/17
 * File: Score.cpp
 *
 * Citation: Abdullah Aghazada's Youtube Tutorial Series: "C++ Qt Game Tutorial"
 * Link to first Video of series: https://www.youtube.com/watch?v=9lqhMLFHj3A&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy
 * Used these videos to get us started learning how to use the Qt library to make a game.
 */


#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;

    // draw the text
    setPlainText(QString("Score: ") + QString::number(score)); // Score: 0
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
}

void Score::increase(){
    score++;
    setPlainText(QString("Score: ") + QString::number(score)); // Score: 1
}

int Score::getScore(){
    return score;
}
