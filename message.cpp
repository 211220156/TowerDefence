#include "message.h"

Message::Message(QWidget *parent)
    : QLabel{parent}
{

}
Message::Message(int x,int y,QString path)
{
    QPixmap p(path);
    this->setFixedSize(p.width(),p.height());
    this->setScaledContents(true);
    this->setPixmap(p);
    this->x=x;
    this->y=y;
    this->active=true;
    this->timer = new QTimer(this);
    this->timer->start(3000);
    connect(this->timer,&QTimer::timeout,this,[=](){
        this->active=false;
    });
}
