#ifndef PLANT_H
#define PLANT_H

#include <QMainWindow>
#include "gameobject.h"
//#include "zombie.h"
#include <QTimer>
#include <QVector>
using std::vector;
//#include "gamescene.h"
class Zombie;
class Plant : public gameObject
{
    Q_OBJECT
public:
    explicit Plant(QWidget *parent = nullptr);
    virtual void act()=0;

    Plant(int x,int y, int blood,int cost,int attackPower,int attackRange,int attackSpeed,int blockUnits/*,GameScene * scene*/);
    virtual int getCost();

    vector<Zombie*> currBlockUnits;
    vector<Zombie*> attackUnits;
    QString bullet="";

    //判断是否为直线攻击
    bool judgeLineAttack();

    int getBlockUnits();

    int getAttackPower();
    int getAttackRange();
    int getAttackSpeed();
    int direction=-1;

    bool isTower=false;
protected:
    int cost;
    int attackPower;
    int blockUnits;
    int attackRange=100;
    int attackSpeed=1;
    bool lineAttack=false;


signals:

};

#endif // PLANT_H
