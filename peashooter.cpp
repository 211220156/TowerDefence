#include "peashooter.h"

Peashooter::Peashooter(QWidget *parent)
    : Plant{parent}
{

}
Peashooter::Peashooter(int x,int y,int blood,QString bullet,int direction,int cost,int attackPower,int attackRange,int attackSpeed,int blockUnits):Plant(x,y,blood,100,5,2000,2,5)
{
    this->resize(110,120);
    this->timer=new QTimer(this);
    this->timer->start(2000);
    this->second=0;
    this->bullet=bullet;
    this->direction=direction;
    this->lineAttack=true;
    connect(this->timer,&QTimer::timeout,this,[=](){
        this->act();
    });
}
void Peashooter::act()
{
    if (this->isAlive){
        this->attackUnits.clear();
        Zombie* nearest=NULL;
        for (int i=0;i<zombies.size();i++){
            if (zombies[i]->isAlive && zombies[i]->y==this->x*113+173 && ((zombies[i]->x<this->y*105+652 && this->direction==0) || (zombies[i]->x>this->y*105+652 && this->direction==1) )){
                if (nearest==NULL){
                    nearest=zombies[i];
                } else {
                    if (abs(zombies[i]->x-(this->y*105+652))<abs(nearest->x-(this->y*105+652))){
                        nearest=zombies[i];
                    }
                }
            }
        }
        if (nearest!=NULL){
            this->attackUnits.push_back(nearest);
            nearest->hit(this->attackPower);
            if (nearest->blood<=0){
                nearest->isAlive=false;
                nearest->second=0;
            }
        }
    }
}
Peashooter::~Peashooter()
{

}
int Peashooter::getCost()
{
    return this->cost;
}
void Peashooter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (this->isAlive){
        if (this->second<=3){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter1_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter1.png"));
            }
        }
        if (this->second>3 && this->second<=6){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter2_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter2.png"));
            }
        }
        if (this->second>6 && this->second<=9){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter3_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter3.png"));
            }
        }
        if (this->second>9 && this->second<=12){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter4_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter4.png"));
            }
        }
        if (this->second>12 && this->second<=15){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter5_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter5.png"));
            }
        }
        if (this->second>15 && this->second<=18){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter6_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter6.png"));
            }
        }
        if (this->second>18 && this->second<=21){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter7_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter7.png"));
            }
        }
        if (this->second>21 && this->second<=24){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter8_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter8.png"));
            }
        }
        if (this->second>24 && this->second<=27){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter9_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter9.png"));
            }
        }
        if (this->second>27 && this->second<=30){
            if (this->direction==0){//表示向左
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter10_left.png"));
            } else {
                painter.drawPixmap(0,0,QPixmap(":/res/Peashooter10.png"));
            }
        }
        if (this->second>=30){
            this->second=0;
        }

        double percent=double(this->blood)/double(this->maxblood);
        painter.fillRect(QRect(12,0,75*percent,7), QBrush(Qt::green));
    }
}
