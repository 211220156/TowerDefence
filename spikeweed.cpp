#include "spikeweed.h"

Spikeweed::Spikeweed(QWidget *parent)
    : Plant{parent}
{

}
void Spikeweed::act()
{
    if (this->isAlive){
        //将攻击的单位放一起
        vector<Zombie*> temp;
        for (int i=0;i<zombies.size();i++){
            if (abs(this->x*113+173+113/2-zombies[i]->y)<=this->attackRange && abs(this->y*105+652+105/2-zombies[i]->x)<=this->attackRange && zombies[i]->isAlive){
                zombies[i]->hit(this->attackPower);
                temp.push_back(zombies[i]);
                if (zombies[i]->blood<=0) {
                    zombies[i]->isAlive=false;
                    zombies[i]->second=0;
                }
                qDebug()<<"地刺发动攻击！";
            }
        }
        this->attackUnits=temp;
    }
}
Spikeweed::Spikeweed(int x,int y,int blood,int cost,int attackPower,int attackRange,int attackSpeed,int blockUnits):Plant(x,y,blood,100,10,80,2,0)
{
    this->resize(100,119);
    this->timer=new QTimer(this);
    this->timer->start(2000);
    this->second=0;
    connect(this->timer,&QTimer::timeout,this,[=](){
        this->act();
    });
}
Spikeweed::~Spikeweed()
{

}
int Spikeweed::getCost()
{
    return this->cost;
}
void Spikeweed::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (this->isAlive){
        if (this->second<=3){
            painter.drawPixmap(10,75,QPixmap(":/res/Spikeweed0.png"));
        }
        if (this->second>3 && this->second<=6){
            painter.drawPixmap(10,75,QPixmap(":/res/Spikeweed1.png"));
        }
        if (this->second>6 && this->second<=9){
            painter.drawPixmap(10,75,QPixmap(":/res/Spikeweed2.png"));
        }
        if (this->second>9 && this->second<=12){
            painter.drawPixmap(10,75,QPixmap(":/res/Spikeweed3.png"));
        }
        if (this->second>12 && this->second<=15){
            painter.drawPixmap(10,75,QPixmap(":/res/Spikeweed4.png"));
        }
        if (this->second>15 && this->second<=18){
            painter.drawPixmap(10,75,QPixmap(":/res/Spikeweed5.png"));
        }
        if (this->second>18 && this->second<=21){
            painter.drawPixmap(10,75,QPixmap(":/res/Spikeweed6.png"));
        }
        if (this->second>21 && this->second<=24){
            painter.drawPixmap(10,75,QPixmap(":/res/Spikeweed7.png"));
        }
        if (this->second>=24){
            this->second=0;
        }
        double percent=double(this->blood)/double(this->maxblood);
        painter.fillRect(QRect(12,0,75*percent,7), QBrush(Qt::green));
    }
}
