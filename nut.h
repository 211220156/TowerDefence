#ifndef NUT_H
#define NUT_H

#include <QWidget>
#include "plant.h"
#include <QMovie>
#include <QPainter>
#include <QPaintEvent>
class Nut : public Plant
{
    Q_OBJECT
public:
    explicit Nut(QWidget *parent = nullptr);
    void act();
    Nut(int x,int y,int blood=100,QString moviePath="",int cost=50,int attackPower=0,int attackRange=0,int attackSpeed=0,int blockUnits=5);
    ~Nut();
    int getCost();

    void paintEvent(QPaintEvent *);
protected:
    QMovie * movie;
    int maxblood=100;

signals:

};

#endif // NUT_H
