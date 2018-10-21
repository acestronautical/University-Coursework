/* Project: Java Defender (Andy's Face In Space Defending the Base)
 * Programmers: Arrin Bevers, Kiernan, Ace Cassidy, Garrick Hutcheson
 * Date: 12/6/17
 * File: Player.h
 *
 * Citation: Abdullah Aghazada's Youtube Tutorial Series: "C++ Qt Game Tutorial"
 * Link to first Video of series: https://www.youtube.com/watch?v=9lqhMLFHj3A&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy
 * Used these videos to get us started learning how to use the Qt library to make a game.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>


class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

    bool left;
    bool right;
    bool up;
    bool down;
    bool shooting;
public slots:
    void spawn();
    void move();
    void shoot();

};

#endif // PLAYER_H
