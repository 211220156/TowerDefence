#ifndef FLAGZOMBIE_H
#define FLAGZOMBIE_H

#include <QMainWindow>
#include "zombie.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "plant.h"
extern vector<Plant*> plants;
class flagZombie : public Zombie
{
    Q_OBJECT
public:
    explicit flagZombie(QWidget *parent = nullptr);
    flagZombie(int x,int y,int pathNumber,QString bullet,int blood=100,int attackPower=5,int attackRange=300,int attackSpeed=3,int moveSpeed=1,bool fly=false);
    void walk();
    void setDirection(vector<vector<Place *>> paths);
    void paintEvent(QPaintEvent *);
    void act();
protected:
    int maxblood=100;

signals:

};

#endif // FLAGZOMBIE_H
