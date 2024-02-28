#include "zombie.h"

Zombie::Zombie(QWidget *parent)
    : gameObject{parent}
{

}
Zombie::Zombie(int x,int y,int blood,int attackPower,int attackRange,int attackSpeed,int moveSpeed,bool fly,int pathNumber):gameObject(x,y,blood)
{
    this->attackPower=attackPower;
    this->attackRange=attackRange;
    this->moveSpeed=moveSpeed;
    this->fly=fly;
    this->attackSpeed=attackSpeed;
    this->pathNumber=pathNumber;
}

void Zombie::hit(int damage)
{
    this->blood-=damage;
}

int Zombie::getDirection()
{
    return direction;
}
void Zombie::setBlocked(bool status)
{
    this->blocked = status;
}
bool Zombie::isFly()
{
    return this->fly;
}
int Zombie::getAttackSpeed()
{
    return this->attackSpeed;
}
int Zombie::getAttackRange()
{
    return this->attackRange;
}
