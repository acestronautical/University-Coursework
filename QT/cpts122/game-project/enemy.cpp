/* Project: Java Defender (Andy's Face In Space Defending the Base)
 * Programmers: Arrin Bevers, Kiernan, Ace Cassidy, Garrick Hutcheson
 * Date: 12/6/17
 * File: Enemy.cpp
 *
 * Citation: Abdullah Aghazada's Youtube Tutorial Series: "C++ Qt Game Tutorial"
 * Link to first Video of series: https://www.youtube.com/watch?v=9lqhMLFHj3A&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy
 * Used these videos to get us started learning how to use the Qt library to make a game.
 */


#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "Game.h"
#include <typeinfo>

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    //set random x position
    int random_number = rand() % 1266;
    setPos(random_number,0);

    int icon = rand() % 3;
    // drew the enemy
    if(icon == 0){
        setPixmap(QPixmap(":/images/javaCup.png"));
    }
    else if (icon == 1){
        setPixmap(QPixmap(":/images/javaCup2.png"));
    }
    else if (icon == 2){
        setPixmap(QPixmap(":/images/javaCup3.png"));
    }

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
}

void Enemy::move(){


    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Player)){
            // decrease health
            game->health->decrease();

            // remove them from the scene (still on the heap)
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete this;

            // return (all code below refers to a non existent enemy)
            return;
        }
    }
    // move enemy down
    setPos(x(),y()+5);

    // destroy enemy when it goes out of the screen
    if (pos().y() > scene()->height() - pixmap().height()){
        //decrease the health
        game->health->decrease();

        scene()->removeItem(this);
        delete this;
    }
}
