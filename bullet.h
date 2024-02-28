#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QLabel>
#include <QDebug>
#include <QPropertyAnimation>
class Bullet : public QLabel
{
    Q_OBJECT
public:
    explicit Bullet(QWidget *parent = nullptr);

    QString image;
    Bullet(int x,int y,int targetX,int targetY,QString image);
    void fly();
    ~Bullet();
    int x;
    int y;
    int targetX;
    int targetY;

signals:

};

#endif // BULLET_H
