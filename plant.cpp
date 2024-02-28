#include "plant.h"

Plant::Plant(QWidget *parent)
    : gameObject{parent}
{

}
Plant::Plant(int x,int y, int blood,int cost,int attackPower,int attackRange,int attackSpeed,int blockUnits/*,GameScene * scene*/):gameObject(x,y,blood/*,scene*/)
{
    this->cost=cost;
    this->attackPower=attackPower;
    this->blockUnits=blockUnits;
    this->attackRange=attackRange;
    this->attackSpeed=attackSpeed;
}
int Plant::getCost()
{
    return this->cost;
}
int Plant::getBlockUnits()
{
    return this->blockUnits;
}
int Plant::getAttackPower()
{
    return this->attackPower;
}
int Plant::getAttackRange()
{
    return this->attackRange;
}
int Plant::getAttackSpeed()
{
    return this->attackSpeed;
}
bool Plant::judgeLineAttack()
{
    return this->lineAttack;
}
