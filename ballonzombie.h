#ifndef BALLONZOMBIE_H
#define BALLONZOMBIE_H

#include <QMainWindow>
#include "zombie.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include "plant.h"
#include <QPixmap>
class ballonZombie : public Zombie
{
    Q_OBJECT
public:
    explicit ballonZombie(QWidget *parent = nullptr);
    void walk();
    ballonZombie(int x,int y,int pathNumber,int blood=100,int attackPower=0,int attackRange=0,int attackSpeed=0,int moveSpeed=1,bool fly=true);
    void setDirection(vector<vector<Place *>> paths);
    void paintEvent(QPaintEvent *);
    void act();
protected:
    int maxblood=100;


signals:

};

#endif // BALLONZOMBIE_H
