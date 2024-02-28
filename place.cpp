#include "place.h"

Place::Place(QWidget *parent)
    : QWidget{parent}
{

}

Place::Place(bool landPath,bool flyPath,bool towerPos,bool forbidden,int x,int y)
{
    this->landPath=landPath;
    this->flyPath=flyPath;
    this->towerPos=towerPos;
    this->forbidden=forbidden;
    this->x=x;
    this->y=y;
}



bool Place::isLandPath()
{
    return this->landPath;
}
bool Place::isFlyPath()
{
    return this->flyPath;
}
bool Place::isTowerPos()
{
    return this->towerPos;
}
bool Place::isForbidden()
{
    return this->forbidden;
}
int Place::getX()
{
    return this->x;
}
int Place::getY()
{
    return this->y;
}
