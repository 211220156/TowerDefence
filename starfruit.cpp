#include "starfruit.h"

StarFruit::StarFruit(QWidget *parent)
    : Plant{parent}
{

}
StarFruit::StarFruit(int x,int y,int blood,QString bullet,int cost,int attackPower,int attackRange,int attackSpeed,int blockUnits):Plant(x,y,blood,125,5,380,2,0)
{
    this->resize(110,119);
    this->timer=new QTimer(this);
    this->timer->start(2000);
    this->second=0;
    this->bullet=bullet;
    this->isTower=true;
//    qDebug()<<"在starfruit构造函数内";
    connect(this->timer,&QTimer::timeout,this,[=](){
        this->act();
    });
}
void StarFruit::act()
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

            }
        }
        this->attackUnits=temp;
    }
}
StarFruit::~StarFruit()
{

}
int StarFruit::getCost()
{
    return this->cost;
}
void StarFruit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (this->isAlive){
        painter.drawPixmap(-18,-40,QPixmap(":/res/starfruit.png"));
        double percent=double(this->blood)/double(this->maxblood);
        painter.fillRect(QRect(12,0,75*percent,7), QBrush(Qt::green));



    }
}
