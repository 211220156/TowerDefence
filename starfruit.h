#ifndef STARFRUIT_H
#define STARFRUIT_H

#include <QMainWindow>
#include "plant.h"
#include <QPainter>
#include <QPaintEvent>
#include "zombie.h"
#include <QDebug>
#include "bullet.h"
extern vector<Zombie*> zombies;
class StarFruit : public Plant
{
    Q_OBJECT
public:
    explicit StarFruit(QWidget *parent = nullptr);
    void act();
    StarFruit(int x,int y,int blood=100,QString bullet="",int cost=125,int attackPower=5,int attackRange=380,int attackSpeed=2,int blockUnits=0);

    ~StarFruit();
    int getCost();



    void paintEvent(QPaintEvent *event);
protected:
    int maxblood=100;

signals:

};

#endif // STARFRUIT_H
