/* Project: Java Defender (Andy's Face In Space Defending the Base)
 * Programmers: Arrin Bevers, Kiernan, Ace Cassidy, Garrick Hutcheson
 * Date: 12/6/17
 * File: Player.cpp
 *
 * Citation: Abdullah Aghazada's Youtube Tutorial Series: "C++ Qt Game Tutorial"
 * Link to first Video of series: https://www.youtube.com/watch?v=9lqhMLFHj3A&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy
 * Used these videos to get us started learning how to use the Qt library to make a game.
 */


#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"
#include <QDebug>

Player::Player(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent) {
setPixmap(QPixmap(":/images/Andy.png"));
left = false;
right = false;
up = false;
down = false;
shooting = false;
}

//This is an ovverriden function from the QObject Class
//When a key event of type press is generated with the player object focused
//This Function will recieve the event
void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_A){
        left = true;
    }
    else if (event->key() == (Qt::Key_D)){
        right = true;
    }

    else if (event->key() == (Qt::Key_W)){
        up = true;
    }
    else if (event->key() == (Qt::Key_S)){
        down = true;
    }
    else if (event->key() == Qt::Key_Space){
        shooting = true;
    }
}


//This is an ovverriden function from the QObject Class
//When a key event of type press is generated with the player object focused
//This Function will recieve the event
void Player::keyReleaseEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_A){
        left = false;
    }
    else if (event->key() == (Qt::Key_D)){
        right = false;
    }

    else if (event->key() == (Qt::Key_W)){
        up = false;
    }
    else if (event->key() == (Qt::Key_S)){
        down = false;
    }

    if (event->key() == Qt::Key_Space){
        shooting = false;
    }
}


//slot function. Generates an enemy and adds it to the scene when it
//recieves a signal
void Player::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}

//slot function. Moves player according to player's current boolean values of left, right, up, and down.
//activates when it recieves a signal
void Player::move()
{
    //qDebug() << "In Player::move()";
    if (left == true){
        if (pos().x() > 0)
            setPos(x()-1.5,y());
    }
    if (right == true){
        if (pos().x() + 100 < scene()->width())
         setPos(x()+1.5,y());
    }

    if (up == true){
        if (pos().y() > 0)
         setPos(x(),y()-1.5);
    }
    if (down == true){
        if (pos().y() + this->pixmap().height() < scene()->height())
            setPos(x(),y()+1.5);
    }
}

//slot function. Makes player shoot if shooting value is true and function is called by signal.
void Player::shoot()
{
    if(shooting == true){
        Bullet * bullet = new Bullet();
        bullet->setPos(x() + pixmap().width()/2 -6, y() + 120);
        scene()->addItem(bullet);
    }
}
