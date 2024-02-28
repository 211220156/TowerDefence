#include "flagzombie.h"

flagZombie::flagZombie(QWidget *parent)
    : Zombie{parent}
{

}
flagZombie::flagZombie(int x,int y,int pathNumber,QString bullet,int blood,int attackPower,int attackRange,int attackSpeed,int moveSpeed,bool fly):Zombie(x,y,blood,attackPower,attackRange,attackSpeed,moveSpeed,fly,pathNumber)
{
    this->resize(109,119);
    this->timer=new QTimer(this);
    this->timer->start(4000);
    this->second=0;
    this->bullet=bullet;
    connect(this->timer,&QTimer::timeout,[=](){
        this->act();
    });
}
void flagZombie::setDirection(vector<vector<Place*>> paths)
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
void flagZombie::walk()
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
void flagZombie::act()
{
    if (this->isAlive){
        vector<Plant*> temp;
        for (int i=0;i<plants.size();i++){
            if (abs(this->y-(plants[i]->x*113+173+113/2))<=this->attackRange && abs(plants[i]->y*105+652+105/2-this->x)<=this->attackRange && plants[i]->isAlive && !plants[i]->isTower){
                plants[i]->blood-=this->attackPower;
                temp.push_back(plants[i]);
                if (plants[i]->blood<=0) {
                    plants[i]->isAlive=false;
                }
            }
        }
        this->attackUnits=temp;
    }
}

void flagZombie::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (this->isAlive){
        if (this->blocked){
                if (this->direction==3){
                    painter.drawPixmap(10,-10,QPixmap(":/res/b_fz1.png"));
                } else {
                    painter.drawPixmap(0,-10,QPixmap(":/res/b_fz1_r.png"));
                }

        } else {
            if (this->second<=15){
                if (this->direction==3){
                    painter.drawPixmap(-40,-10,QPixmap(":/res/flagZombie1.png"));
                } else {
                    painter.drawPixmap(0,-10,QPixmap(":/res/flagZombie1_right.png"));
                }
            }
            if (this->second>15 && this->second<=30){
                if (this->direction==3){
                    painter.drawPixmap(-40,-10,QPixmap(":/res/flagZombie2.png"));
                } else {
                    painter.drawPixmap(0,-10,QPixmap(":/res/flagZombie2_right.png"));
                }
            }
            if (this->second>=30){
                this->second=0;
            }
        }
        double percent=double(this->blood)/double(this->maxblood);//画血条
        painter.fillRect(QRect(20,0,75*percent,6), QBrush(Qt::red));
    } else {//死亡动画
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
