#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QMainWindow>
#include <QLabel>
//#include "gamescene.h"
class gameObject : public QLabel
{
    Q_OBJECT
public:
    explicit gameObject(QWidget *parent = nullptr);

    gameObject(int x=0,int y=0,int blood=0/*,GameScene * scene=NULL*/);

    bool isAlive=true;
    QTimer * timer;
    int second;
    int blood;
    int x,y;

    bool showAttackRange=false;
signals:

};

#endif // GAMEOBJECT_H
