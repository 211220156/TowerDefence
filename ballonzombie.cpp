#include "ballonzombie.h"

ballonZombie::ballonZombie(QWidget *parent)
    : Zombie{parent}
{

}
ballonZombie::ballonZombie(int x,int y,int pathNumber,int blood,int attackPower,int attackRange,int attackSpeed,int moveSpeed,bool fly):Zombie(x,y,blood,attackPower,attackRange,attackSpeed,moveSpeed,fly,pathNumber)
{
    this->resize(108,119);
    this->timer = new QTimer(this);
    this->timer->start(2000);//暂无作用
    this->second=0;
}
void ballonZombie::walk()
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
void ballonZombie::setDirection(vector<vector<Place *>> paths)
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

void ballonZombie::act()
{

}
void ballonZombie::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (this->isAlive){
        if (this->direction==3){
            painter.drawPixmap(0,-10,QPixmap(":/res/ballonZombie.png"));
        } else {
            painter.drawPixmap(0,-10,QPixmap(":/res/ballonZombie_right.png"));
        }
        double percent=double(this->blood)/double(this->maxblood);
        painter.fillRect(QRect(20,0,75*percent,6), QBrush(Qt::red));
    }
}
