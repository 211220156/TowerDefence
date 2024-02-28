#include "beginbutton.h"

beginButton::beginButton(QWidget *parent)
    : QPushButton{parent}
{

}

beginButton::beginButton(QString normalImg, QString pressImg)
{
    normalImgPath = normalImg;
    pressedImgPath = pressImg;
    QPixmap p(normalImg);

    this->setFixedSize(p.width(),p.height());

    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(p);

    this->setIconSize(QSize(p.width(),p.height()));
}

void beginButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * a1 = new QPropertyAnimation(this,"geometry");
    a1->setDuration(200);

    a1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    a1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置缓和曲线
    a1->setEasingCurve(QEasingCurve::OutBounce);//弹起效果
    //执行动画
    a1->start();

}

void beginButton::zoom2()
{
    QPropertyAnimation * a1 = new QPropertyAnimation(this,"geometry");
    a1->setDuration(200);

    a1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    a1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置缓和曲线
    a1->setEasingCurve(QEasingCurve::OutBounce);//弹起效果
    //执行动画
    a1->start();

}
