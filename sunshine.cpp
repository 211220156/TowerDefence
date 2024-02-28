#include "sunshine.h"

sunshine::sunshine(QWidget *parent)
    : QLabel{parent}
{

}
sunshine::sunshine(int x,int y,int targetY)
{
    this->x=x;
    this->y=y;
    this->targetY=targetY;
    this->timer=new QTimer(this);
    this->timer->start(20);

    QPixmap p(":/res/sunshine.png");
    this->setFixedSize(77,77);

    this->setScaledContents(true);
    this->setPixmap(p);

    connect(this->timer,&QTimer::timeout,[=](){
        if (catched==true && round<40){
            round++;
        }
        if ((round==40 && catched) || (round==600 && !catched)){//长时间不拾取也会消失
            this->disappeared=true;
        }
        if (catched==false && this->y<this->targetY){
            this->y+=3;
        }
        if (this->y>=this->targetY && catched==false){
            round++;
        }

    });
}
void sunshine::fly()
{
    QPropertyAnimation * s = new QPropertyAnimation(this,"geometry");
    s->setDuration(800);

    s->setStartValue(QRect(this->x,this->y,this->width(),this->height()));
    s->setEndValue(QRect(20,43,this->width(),this->height()));

    this->catched=true;
    s->start();
}
sunshine::~sunshine()
{

}
