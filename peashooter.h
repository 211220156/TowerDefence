#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <QMainWindow>
#include "plant.h"
#include <QPainter>
#include <QPaintEvent>
#include "zombie.h"
#include <QDebug>
#include "bullet.h"
extern vector<Zombie*> zombies;
class Peashooter : public Plant
{
    Q_OBJECT
public:
    explicit Peashooter(QWidget *parent = nullptr);
    void act();
    Peashooter(int x,int y,int blood=100,QString bullet="",int direction=0,int cost=100,int attackPower=5,int attackRange=2000,int attackSpeed=2,int blockUnits=5);

    ~Peashooter();
    int getCost();

    void paintEvent(QPaintEvent *);
protected:
    int maxblood=100;

signals:

};

#endif // PEASHOOTER_H
