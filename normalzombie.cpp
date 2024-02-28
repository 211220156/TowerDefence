#include "normalzombie.h"

normalZombie::normalZombie(QWidget *parent)
    : Zombie{parent}
{

}

void normalZombie::act()
{
    if (this->isAlive){
        for (int i=0;i<plants.size();i++){
            if (plants[i]->isAlive && count(plants[i]->currBlockUnits.begin(),plants[i]->currBlockUnits.end(),this)){
                    plants[i]->blood-=this->attackPower;

                    qDebug()<<"僵尸发动了攻击";
                    qDebug()<<"剩余血量："<<plants[i]->blood;
                    if (plants[i]->blood<=0){
                        plants[i]->isAlive=false;
                        plants[i]->currBlockUnits.clear();

                    }
                    break;//单回合只攻击一次
            }
        }
    }
}
void normalZombie::walk()
{

    if (!this->blocked){//僵尸没被挡住才能走
        if (this->direction==1)//向上
        {
            this->y-=this->moveSpeed;
        }
        if (this->direction==2)//向下
        {
            this->y+=this->moveSpeed;
        }
        if (this->direction==3)//向左
        {
            this->x-=this->moveSpeed;
        }
        if (this->direction==4)//向右
        {
            this->x+=this->moveSpeed;
        }
    }
}
normalZombie::normalZombie(int x,int y,int pathNumber,int blood,int attackPower,int attackRange,int attackSpeed,int moveSpeed,bool fly):Zombie(x,y,blood,attackPower,attackRange,attackSpeed,moveSpeed,fly,pathNumber)
{
    this->resize(108,119);
    this->timer = new QTimer(this);
    this->timer->start(2000);
    this->second=0;
    connect(this->timer,&QTimer::timeout,[=](){
        this->act();
    });
}
void normalZombie::setDirection(vector<vector<Place*>> paths)
{
    for (int i=0;i<paths[pathNumber].size();i++){
        if (x==paths[pathNumber][i]->y*105+652 && y==paths[pathNumber][i]->x*113+173){
            if (paths[pathNumber][i+1]->x==paths[pathNumber][i]->x+1){//往下
                this->direction=2;
            }
            if (paths[pathNumber][i+1]->x==paths[pathNumber][i]->x-1){//往上
                this->direction=1;
            }
            if (paths[pathNumber][i+1]->y==paths[pathNumber][i]->y+1){//往右
                this->direction=4;
            }
            if (paths[pathNumber][i+1]->y==paths[pathNumber][i]->y-1){//往左
                this->direction=3;
            }
            break;
        }
    }
}

void normalZombie::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (this->isAlive){
        if (this->blocked){
            if (this->second<=10) {
                if (this->direction==3){
                    painter.drawPixmap(-40,-20,QPixmap(":/res/normalZombieEat1.png"));
                } else {
                    painter.drawPixmap(-10,-20,QPixmap(":/res/normalZombieEat1_right.png"));
                }
            }
            if (this->second>=10 && this->second<=20) {
                if (this->direction==3){
                    painter.drawPixmap(-40,-20,QPixmap(":/res/normalZombieEat2.png"));
                } else {
                    painter.drawPixmap(-10,-20,QPixmap(":/res/normalZombieEat2_right.png"));
                }
            }
            if (this->second>=20){
                this->second=0;
            }
        } else {
            if (this->second<=10){
                if (this->direction==3){
                    painter.drawPixmap(0,0,QPixmap(":/res/normalZombie_left.png"));
                } else {
                    painter.drawPixmap(0,0,QPixmap(":/res/normalZombie.png"));
                }
            }
            if (this->second>10 && this->second<=20){
                if (this->direction==3){
                    painter.drawPixmap(20,0,QPixmap(":/res/normalZombie2.png"));
                } else {
                    painter.drawPixmap(0,0,QPixmap(":/res/normalZombie2_right.png"));
                }
            }
            if (this->second>=20){
                this->second=0;
            }
        }
        double percent=double(this->blood)/double(this->maxblood);
        painter.fillRect(QRect(20,0,75*percent,6), QBrush(Qt::red));
    } else {
        if (this->second<=30){
            if (this->direction==3){
                painter.drawPixmap(-20,-30,QPixmap(":/res/dying1.png"));
            } else {
                painter.drawPixmap(-20,-30,QPixmap(":/res/dying1_right.png"));
            }
        }
        if (this->second>30 && this->second<=60){
            if (this->direction==3){
                painter.drawPixmap(0,40,QPixmap(":/res/dying2.png"));
            } else {
                painter.drawPixmap(0,40,QPixmap(":/res/dying2_right.png"));
            }
        }
    }
}
