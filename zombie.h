#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QMainWindow>
#include "gameobject.h"
#include "place.h"
//#include "plant.h"
class Plant;

class Zombie : public gameObject
{
    Q_OBJECT
public:
    explicit Zombie(QWidget *parent = nullptr);
    virtual void act()=0;
    virtual void walk()=0;
    void hit(int damage);//被攻击
    Zombie(int x,int y,int blood,int attackPower,int attackRange=1,int attackSpeed=2,int moveSpeed=10,bool fly=false,int pathNumber=0);
    virtual void setDirection(vector<vector<Place*>>)=0;

    int getDirection();
    void setBlocked(bool status);
    vector<Plant*> attackUnits;
    QString bullet="";


    int pathNumber=0;

    bool isFly();
    int getAttackSpeed();
    int getAttackRange();
protected:
    int attackPower;
    int attackRange=1;
    int moveSpeed=10;
    bool fly=false;
    int direction=1;//1为向下，2为向上，3为向左，4为向右
    bool blocked=false;
    int attackSpeed;

signals:

};

#endif // ZOMBIE_H
