#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include "map.h"
#include "place.h"
#include <QRect>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include "gameobject.h"
#include "plant.h"
#include "nut.h"
#include "starfruit.h"
#include "normalzombie.h"
#include "beginbutton.h"
#include <QRandomGenerator>
#include "bullet.h"
#include "ballonzombie.h"
#include "flagzombie.h"
#include "peashooter.h"
#include "sunshine.h"
#include "message.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "spikeweed.h"
class Zombie;
extern vector<Plant*> plants;
extern vector<Zombie*> zombies;
class GameScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);

    GameScene(Map* map,int gameLevel);
    ~GameScene();
    Map* map;
    void paintEvent(QPaintEvent *event);


    QString preparedPlant="";

    QMediaPlaylist * playlist;
    QMediaPlayer * player;

    void judgeBlocked(Zombie* z);
    bool isPlaceEmpty(int x,int y);
    // 种植植物
    void createPlant(Plant* p);
    //放置僵尸
    void createZombie(Zombie* z);

    //鼠标事件
    void mousePressEvent(QMouseEvent *event);


    bool status=true;//判断游戏结束与否。
    int sunNum=0; //阳光总数
    int beforeGameNum; //判断游戏在进行中还是还未开始
    beginButton * stopbtn;

    vector<Bullet*> allBullet; //所有子弹
    vector<sunshine*> allsunshine; //阳关的集合
    Message * currMess;//当前消息

    QTimer * beforeGame;
    QTimer * timer;
    QTimer * timer2;
    QTimer * timer3;


    int life=20;//大本营生命值

    int level=0;//难度设置 0为简单，1为中等，2为困难
    void lose();

    int second;
signals:

};

#endif // GAMESCENE_H
