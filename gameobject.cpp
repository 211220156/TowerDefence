#include "gameobject.h"

gameObject::gameObject(QWidget *parent)
    : QLabel{parent}
{
    setMouseTracking(true);
}
gameObject::gameObject(int x,int y,int blood/*,GameScene * scene*/)
{
    this->x=x;
    this->y=y;
    this->blood=blood;
}
