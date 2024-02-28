#include "nut.h"

Nut::Nut(QWidget *parent)
    : Plant{parent}
{

}

Nut::Nut(int x,int y,int blood,QString moviePath,int cost,int attackPower,int attackRange,int attackSpeed,int blockUnits/*,GameScene * scene*/):Plant(x,y,100,50,0,0,0,blockUnits/*,scene*/)
{
    movie = new QMovie(moviePath);
    movie->setScaledSize(QSize(108,115));
    this->setMovie(movie);
    this->resize(108,119);
    //无用
    this->timer=new QTimer(this);
    this->timer->start(2000);

    this->second=0;
    qDebug()<<"在坚果的构造函数中";
}
Nut::~Nut()
{
    delete movie;
    movie=NULL;
}

void Nut::act()
{

}


int Nut::getCost()
{
    return this->cost;
}
void Nut::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (this->isAlive){
        if (this->blood>=50){
            painter.drawPixmap(-20,-48,QPixmap(":/res/nut.png"));
        } else {
            painter.drawPixmap(-20,-48,QPixmap(":/res/nut2.png"));
        }
        //画血条
        double percent=double(this->blood)/double(this->maxblood);
        painter.fillRect(QRect(16,0,75*percent,9), QBrush(Qt::green));
    }
}
