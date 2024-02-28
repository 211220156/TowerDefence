#include "bullet.h"

Bullet::Bullet(QWidget *parent)
    : QLabel{parent}
{

}

Bullet::Bullet(int x,int y,int targetX,int targetY,QString image)
{
    qDebug()<<"子弹生成处！";
    this->x=x;
    this->y=y;
    this->image=image;
    this->targetX=targetX;
    this->targetY=targetY;

    QPixmap p(this->image);
    this->setFixedSize(p.width(),p.height());

    this->setScaledContents(true);
    this->setPixmap(p);



}
Bullet::~Bullet()
{

}
void Bullet::fly()
{
    QPropertyAnimation * a = new QPropertyAnimation(this,"geometry");
    a->setDuration(1000);


    a->setStartValue(QRect(this->x,this->y,this->width(),this->height()));
    a->setEndValue(QRect(this->targetX,this->targetY,this->width(),this->height()));

    //设置缓和曲线
    //a->setEasingCurve(QEasingCurve::OutBounce);

    a->start();
}
