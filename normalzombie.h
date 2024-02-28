#ifndef NORMALZOMBIE_H
#define NORMALZOMBIE_H

#include <QMainWindow>
#include "zombie.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "plant.h"
extern vector<Plant*> plants;
class normalZombie : public Zombie
{
    Q_OBJECT
public:
    explicit normalZombie(QWidget *parent = nullptr);
    normalZombie(int x,int y,int pathNumber,int blood=100,int attackPower=10,int attackRange=0,int attackSpeed=2,int moveSpeed=1,bool fly=false);
    void walk();
    void setDirection(vector<vector<Place *>> paths);

    void paintEvent(QPaintEvent *);
    void act();
protected:
    int maxblood=100;
signals:

};

#endif // NORMALZOMBIE_H
