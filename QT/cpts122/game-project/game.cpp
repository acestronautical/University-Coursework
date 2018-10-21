/* Project: Java Defender (Andy's Face In Space Defending the Base)
 * Programmers: Arrin Bevers, Kiernan, Ace Cassidy, Garrick Hutcheson
 * Date: 12/6/17
 * File: Game.cpp
 *
 * Citation: Abdullah Aghazada's Youtube Tutorial Series: "C++ Qt Game Tutorial"
 * Link to first Video of series: https://www.youtube.com/watch?v=9lqhMLFHj3A&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy
 * Used these videos to get us started learning how to use the Qt library to make a game.
 */



#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include <QImage>
#include <QPalette>
#include <QBrush>
#include <QThread>
#include <QDebug>


Game::Game(){

    //create welcome screen
    QPixmap pixmap(":/images/Splash_screen.png");
    QSplashScreen welcome(pixmap);
    welcome.show();
    QThread::sleep(4);

    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1366,768); // make the scene 1366X768 instead of infinity by infinity (default)
    //set scene background
    setBackgroundBrush(QBrush(QImage(":/images/Wsu_Background.png")));

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1366,768);

    // create the player
    player = new Player();
    //player->setRect(0,0,100,100); // change the rect from 0x0 (default) to 100x100 pixels
    player->setPos(400,500); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);

    // add the player to the scene
    scene->addItem(player);
    //all keyboard input now goes to player object
    player->grabKeyboard();


    // create the score/health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    //send signal to player's move function
    QTimer * moveTimer = new QTimer();
    QObject::connect(moveTimer, SIGNAL(timeout()),player,SLOT(move()));
    moveTimer->start(5);

    //send signal to player's shoot function
    QTimer * shootTimer = new QTimer();
    QObject::connect(shootTimer, SIGNAL(timeout()),player,SLOT(shoot()));
    shootTimer->start(300);

    // spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);

    show();
}


//TODO: implement mouse events that shoot bullets toward cursor
void Game::mousePressEvent(QMouseEvent *event)
{
       qDebug() << "Mouse Press";
   if(event->button() == Qt::LeftButton)

   qDebug() << "Mouse Press";
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{
                 qDebug() << "Mouse Release";
    if(event->button() == Qt::LeftButton)
             qDebug() << "Mouse Release";
}
