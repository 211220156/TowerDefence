#ifndef SPIKEWEED_H
#define SPIKEWEED_H

#include <QMainWindow>
#include "plant.h"
#include <QPainter>
#include <QPaintEvent>
#include "zombie.h"
#include <QDebug>
extern vector<Zombie*> zombies;
class Spikeweed : public Plant
{
    Q_OBJECT
public:
    explicit Spikeweed(QWidget *parent = nullptr);

    void act();
    Spikeweed(int x,int y,int blood=1000,int cost=100,int attackPower=10,int attackRange=80,int attackSpeed=200,int blockUnits=0);
    ~Spikeweed();
    int getCost();
    void paintEvent(QPaintEvent *);

protected:
    int maxblood=1000;
signals:

};

#endif // SPIKEWEED_H
