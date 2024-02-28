#include "gamescene.h"
vector<Plant*> plants;
vector<Zombie*> zombies;
GameScene::GameScene(QWidget *parent)
    : QMainWindow{parent}
{

    this->setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
}
GameScene::GameScene(Map* map,int gameLevel)
{
    this->setFixedSize(1920,1080);

    this->map=map;

    this->level=gameLevel;

    this->currMess=NULL;

    this->setWindowIcon(QPixmap(":/res/mainWidgetIcon.png"));

    this->setWindowTitle("抵御入侵中。。。");

    //放音乐
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("C:\\Users\\86139\\Desktop\\TowerDenfence\\res\\bgm2.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("C:\\Users\\86139\\Desktop\\TowerDenfence\\res\\bgm3.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->setCurrentIndex(1);//设置索引
    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->setVolume(25);
    player->play();

    QMenuBar * bar = this->menuBar();

    this->setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("选项");
    QAction * quit = startMenu->addAction("退出游戏");

    connect(quit,&QAction::triggered,this,[=](){
        this->close();
    });

    //初始文字提醒
    beforeGame=new QTimer(this);
    beforeGame->start(2800);
    beforeGameNum=1;
    connect(beforeGame,&QTimer::timeout,[=](){
        beforeGameNum++;//1时为准备阶段，2时为plant，3时进入正常游戏
        if (beforeGameNum<=3){
            update();//要手动调用paintevent
        }
    });

    //阳光自增
    timer=new QTimer(this);
    timer->start(20);
    sunNum=0;
    connect(timer,&QTimer::timeout,[=](){
        if (beforeGameNum>=3){
            //让植物与僵尸自身的时间自增。
            for (int i=0;i<plants.size();i++){
                plants[i]->second++;
                //每一轮重新判定阻挡僵尸
                vector<Zombie*> temp;
                for (int j=0;j<plants[i]->currBlockUnits.size();j++){
                    if (plants[i]->currBlockUnits[j]->isAlive){
                        temp.push_back(plants[i]->currBlockUnits[j]);
                    }
                }
                plants[i]->currBlockUnits=temp;
            }
            for (int i=0;i<zombies.size();i++){
                zombies[i]->second++;
            }

            for (int i=0;i<zombies.size();i++){
                if (zombies[i]->isAlive){
                    if (!zombies[i]->isFly()){
                        zombies[i]->setDirection(map->landPaths);//可以在此处统一的走，若后期要区分不同僵尸的移速，修改walk函数的值
                    } else {
                        zombies[i]->setDirection(map->flyPaths);
                    }
                    zombies[i]->walk();
                    //碰撞判定
                    judgeBlocked(zombies[i]);

                    if (!zombies[i]->isFly() && abs(zombies[i]->x-(map->landPaths[zombies[i]->pathNumber][map->landPaths[zombies[i]->pathNumber].size()-1]->y*105+652))<=3 && abs(zombies[i]->y-(map->landPaths[zombies[i]->pathNumber][map->landPaths[zombies[i]->pathNumber].size()-1]->x*113+173))<=3)
                    {
                        this->life-=1;
                        zombies[i]->isAlive=false;
                        if (this->life==0){
                            qDebug()<<"游戏结束！你输了！";
                            lose();
                            zombies[i]->second=0;
                        }
                    }
                    if (zombies[i]->isFly() && abs(zombies[i]->x-(map->flyPaths[zombies[i]->pathNumber][map->flyPaths[zombies[i]->pathNumber].size()-1]->y*105+652))<=3 && abs(zombies[i]->y-(map->flyPaths[zombies[i]->pathNumber][map->flyPaths[zombies[i]->pathNumber].size()-1]->x*113+173))<=3)
                    {
                        this->life-=1;
                        zombies[i]->isAlive=false;
                        if (this->life==0){
                            qDebug()<<"游戏结束！你输了！";
                            lose();
                            zombies[i]->second=0;
                        }
                    }
                }
            }

            //生成阳光
            if (QRandomGenerator::global()->bounded(250+50*this->level)<=2){
                sunshine * s = new sunshine(QRandomGenerator::global()->bounded(80,1800),0,QRandomGenerator::global()->bounded(300,950));
                s->setParent(this);
                this->allsunshine.push_back(s);
            }
            update();
        }
    });

    //生成僵尸
    timer2 = new QTimer(this);
    timer2->start(5000-1000*this->level);//僵尸生成速度与难度选择挂钩
    connect(timer2,&QTimer::timeout,[=](){
        if (beforeGameNum>=3){
            int i=QRandomGenerator::global()->bounded(0,map->landPaths.size());
            Zombie * z;
            Zombie * b;
            qDebug()<<"血量："<<100+this->second/8;
            qDebug()<<"攻击力："<<10+this->second/15;
            if (QRandomGenerator::global()->bounded(100)%100<=40+this->second/10){
                z= new normalZombie(map->landPaths[i][0]->y*105+652,map->landPaths[i][0]->x*113+173,i,100+this->second/8,10+this->second/15);//血量越来越厚
            } else {
                z = new flagZombie(map->landPaths[i][0]->y*105+652,map->landPaths[i][0]->x*113+173,i,":/res/flagZombieBullet.png",100+this->second/8,5+this->second/15);
            }
            createZombie(z);

            int j=QRandomGenerator::global()->bounded(0,map->flyPaths.size());
            if (QRandomGenerator::global()->bounded(100)%100<=20+this->second/8){
                b= new ballonZombie(map->flyPaths[j][0]->y*105+652,map->flyPaths[j][0]->x*113+173,j,100+this->second/8);
                createZombie(b);
            }


            update();
        }
    });

    //画攻击特效
    timer3 = new QTimer(this);
    timer3->start(1000);
    this->second=0;
    connect(timer3,&QTimer::timeout,[=](){
        if (beforeGameNum>=3){
            for (int i=0;i<this->allBullet.size();i++){

                this->allBullet[i]->close();
                delete this->allBullet[i];
            }
            this->allBullet.clear();
            this->second+=1;
            for (int i=0;i<plants.size();i++){
                if (plants[i]->isAlive && plants[i]->getAttackSpeed()!=0 && this->second%plants[i]->getAttackSpeed()==0 && plants[i]->attackUnits.size()>0){
                    for (int j=0;j<plants[i]->attackUnits.size();j++){
                        Bullet * b;

                        //下面仅仅为了美化豌豆攻击效果
                        if (plants[i]->judgeLineAttack()){
                            qDebug()<<"豌豆射手方向："<<plants[i]->direction;
                            if (plants[i]->direction==0){
                                b = new Bullet(plants[i]->y*105+652+30,plants[i]->x*113+173+30,plants[i]->attackUnits[j]->x+50,plants[i]->attackUnits[j]->y+30,plants[i]->bullet);
                            }
                            if (plants[i]->direction==1){
                                b = new Bullet(plants[i]->y*105+652+70,plants[i]->x*113+173+30,plants[i]->attackUnits[j]->x+50,plants[i]->attackUnits[j]->y+30,plants[i]->bullet);
                            }
                        } else {
                            b = new Bullet(plants[i]->y*105+652+105/2,plants[i]->x*113+173+113/2,plants[i]->attackUnits[j]->x+80,plants[i]->attackUnits[j]->y+50,plants[i]->bullet);
                        }
                        this->allBullet.push_back(b);
                        b->setParent(this);
                        b->show();
                        b->fly();
                    }
                }
            }
            for (int i=0;i<zombies.size();i++){

                if (zombies[i]->isAlive  && zombies[i]->getAttackSpeed()!=0 && this->second%zombies[i]->getAttackSpeed()==0 && zombies[i]->attackUnits.size()>0){
                    for (int j=0;j<zombies[i]->attackUnits.size();j++){
                        Bullet * b = new Bullet(zombies[i]->x+70,zombies[i]->y+20,zombies[i]->attackUnits[j]->y*105+652+105/2,zombies[i]->attackUnits[j]->x*113+173+113/2,zombies[i]->bullet);
                        this->allBullet.push_back(b);
                        b->setParent(this);
                        b->show();
                        b->fly();
                    }
                }
            }
        }
    });

    preparedPlant="";
    QPushButton * nutButton=new QPushButton(this);
    nutButton->resize(90,120);
    nutButton->move(110,40);
    nutButton->setFlat(true);
    nutButton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    connect(nutButton,&QPushButton::clicked,this,[=](){
        if (sunNum>=50 && timer->isActive()){
            preparedPlant="nut";
        }
        if (sunNum<50){
            qDebug()<<"没有足够阳光种坚果";
            Message * m = new Message(620,40,":/res/lackOfSunshine.png");
            m->setParent(this);
            if (this->currMess!=NULL){
                this->currMess->close();
                delete this->currMess;
            }
            this->currMess=m;
        }
    });

    QPushButton * starfruitButton=new QPushButton(this);
    starfruitButton->resize(90,120);
    starfruitButton->move(200,40);
    starfruitButton->setFlat(true);
    starfruitButton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    connect(starfruitButton,&QPushButton::clicked,this,[=](){
        if (sunNum>=125 && timer->isActive()){
            preparedPlant="starfruit";
        }
        if (sunNum<125){
            qDebug()<<"没有足够阳光种杨桃";
            Message * m = new Message(620,40,":/res/lackOfSunshine.png");
            m->setParent(this);
            if (this->currMess!=NULL){
                this->currMess->close();
                delete this->currMess;
            }

            this->currMess=m;
        }
    });

    QPushButton * peashooterButton = new QPushButton(this);
    peashooterButton->resize(90,120);
    peashooterButton->move(290,40);
    peashooterButton->setFlat(true);
    peashooterButton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    connect(peashooterButton,&QPushButton::clicked,this,[=](){
        if (sunNum>=100 && timer->isActive()){
            preparedPlant="peashooter";
        }
        if (sunNum<100){
            qDebug()<<"没有足够阳光种豌豆射手";
            Message * m = new Message(620,40,":/res/lackOfSunshine.png");
            m->setParent(this);
            if (this->currMess!=NULL){
                this->currMess->close();
                delete this->currMess;
            }
            this->currMess=m;
        }
    });

    QPushButton * spikeweedButton=new QPushButton(this);
    spikeweedButton->resize(90,120);
    spikeweedButton->move(380,40);
    spikeweedButton->setFlat(true);
    spikeweedButton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    connect(spikeweedButton,&QPushButton::clicked,this,[=](){
        if (sunNum>=100 && timer->isActive()){
            preparedPlant="Spikeweed";
        }
        if (sunNum<100){
            qDebug()<<"没有足够阳光种地刺";
            Message * m = new Message(620,40,":/res/lackOfSunshine.png");
            m->setParent(this);
            if (this->currMess!=NULL){
                this->currMess->close();
                delete this->currMess;
            }
            this->currMess=m;
        }
    });

    //铲子
    QPushButton * shovel=new QPushButton(this);
    shovel->resize(120,129);
    shovel->move(1600,30);
    shovel->setFlat(true);
    shovel->setStyleSheet("QPushButton{border:none;background:transparent;}");
    connect(shovel,&QPushButton::clicked,this,[=](){
        if (timer->isActive()){
            preparedPlant="shovel";
        }
    });

    //暂停按钮
    stopbtn=new beginButton(":/res/stopbtn.png");
    stopbtn->setParent(this);
    stopbtn->move(1770,30);

    connect(stopbtn,&QPushButton::clicked,this,[=](){
        if (status==true){
            stopbtn->zoom1();
            stopbtn->zoom2();
            if (timer->isActive()){
                beforeGame->stop();
                timer->stop();
                timer2->stop();
                timer3->stop();
                for (int i=0;i<zombies.size();i++){
                    zombies[i]->timer->stop();
                }
                for (int i=0;i<plants.size();i++){
                    plants[i]->timer->stop();
                }

            } else {
                beforeGame->start(2800);
                timer->start(20);
                timer2->start(2000);
                timer3->start(1000);
                for (int i=0;i<zombies.size();i++){
                    zombies[i]->timer->start(2000);//后面要修改！根据僵尸自身的属性
                }
                for (int i=0;i<plants.size();i++){
                    plants[i]->timer->start();
                }
            }
        }
    });

}
void GameScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    QPixmap pixmap(":/res/05.jpg");
    pixmap = pixmap.scaled(1920,1080, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0,0,pixmap);

    for (int i=0;i<map->scene.size();i++){
        for (int j=0;j<map->scene[0].size();j++){
            if (map->scene[i][j]->landPath && !map->scene[i][j]->flyPath){
                painter.drawPixmap(652+105*j,173+113*i,105,113,QPixmap(":/res/ground.jpg"));
            }
            if (map->scene[i][j]->towerPos){
                painter.drawPixmap(652+105*j,173+113*i,105,113,QPixmap(":/res/leaf.jpg"));
            }
            if (map->scene[i][j]->forbidden){
                painter.drawPixmap(652+105*j,173+113*i,105,113,QPixmap(":/res/water2.jpg"));
            }
            if (map->scene[i][j]->flyPath && !map->scene[i][j]->landPath){
                painter.drawPixmap(652+105*j,173+113*i,105,113,QPixmap(":/res/flyPath.jpg"));
            }
            if (map->scene[i][j]->flyPath && map->scene[i][j]->landPath){
                painter.drawPixmap(652+105*j,173+113*i,105,113,QPixmap(":/res/bothPath.jpg"));
            }
            if (map->scene[i][j]->firstPlace){
                painter.drawPixmap(652+105*j,173+113*i,105,113,QPixmap(":/res/firstPlace.png"));

            }
            if (map->scene[i][j]->lastPlace){
                painter.drawPixmap(652+105*j,173+113*i,105,113,QPixmap(":/res/lastPlace.png"));
                double percent=double(this->life)/double(20);
                painter.fillRect(QRect(652+105*j+12,173+113*i,75*percent,7), QBrush(Qt::blue));
            }
        }
    }
    //打印展示植物的栏位
    painter.drawPixmap(0,30,620,147,QPixmap(":/res/cardBg.png"));
    painter.drawText(45,153,QString::number(sunNum));
    //画铲子
    painter.drawPixmap(1600,30,120,129,QPixmap(":/res/shovel.png"));

    painter.drawPixmap(110,40,90,120,QPixmap(":/res/nutCard.png"));//画坚果
    painter.drawPixmap(177,14,135,175,QPixmap(":/res/starfruitCard.png"));//画杨桃
    painter.drawPixmap(265,14,135,175,QPixmap(":/res/PeashooterCard.png"));//画豌豆射手
    painter.drawPixmap(353,14,135,175,QPixmap(":/res/SpikeweedCard.png"));//画地刺

    //打印刚开始的文字
    if (beforeGameNum==1){
        painter.drawPixmap(920,530,QPixmap(":/res/ready.png"));
    }
    if (beforeGameNum==2){
        painter.drawPixmap(920,530,QPixmap(":/res/plant.png"));
    }

    //打印提醒消息
    if (this->currMess!=NULL){
        if (!this->currMess->active){
            this->currMess->close();
        } else {
            this->currMess->move(this->currMess->x,this->currMess->y);
            this->currMess->show();
        }
    }

    if (status==false){
        for (int i=0;i<plants.size();i++){
            plants[i]->close();
        }
        for (int i=0;i<zombies.size();i++){
            zombies[i]->close();
        }
        painter.drawPixmap(460,115,1000,842,QPixmap(":/res/lose.jpeg"));
    } else {
        for (int i=0;i<plants.size();i++){
            if (plants[i]->isAlive){
                plants[i]->move(652+105*plants[i]->y,173+113*plants[i]->x);
                plants[i]->show();//画图事件的调用与show无关！要在画图事件中也加入对生物是否存活的判断！

                //画攻击范围
                if (plants[i]->showAttackRange){
                    QPen pen(Qt::green);
                    painter.setPen(pen);
                    if (!plants[i]->judgeLineAttack()){//不是直线攻击才画范围
                        painter.drawRect(plants[i]->y*105+652+105/2-plants[i]->getAttackRange(),plants[i]->x*113+173+113/2-plants[i]->getAttackRange(),2*plants[i]->getAttackRange(),2*plants[i]->getAttackRange());
                    }
                }

            }
        }
        for (int i=0;i<zombies.size();i++){
            if (zombies[i]->isAlive){
                zombies[i]->move(zombies[i]->x,zombies[i]->y);
                zombies[i]->show();

                //攻击范围
                if (zombies[i]->showAttackRange){
                    QPen pen(Qt::red);
                    painter.setPen(pen);
                    painter.drawRect(zombies[i]->x+80-zombies[i]->getAttackRange(),zombies[i]->y+20-zombies[i]->getAttackRange(),2*zombies[i]->getAttackRange(),2*zombies[i]->getAttackRange());
                }

            } else if (zombies[i]->second<=60){//便于播放死亡特效
                zombies[i]->show();
            }
        }

        //打印阳光
        for (int i=0;i<this->allsunshine.size();i++){
            if (allsunshine[i]->catched==false){
                allsunshine[i]->move(allsunshine[i]->x,allsunshine[i]->y);
            }
            if (allsunshine[i]->disappeared==false){
                allsunshine[i]->show();
            } else {
                allsunshine[i]->close();
            }
        }
    }

}

void GameScene::createPlant(Plant* p)
{
    plants.push_back(p);
    p->setParent(this);
    this->sunNum-=p->getCost();
}

void GameScene::createZombie(Zombie* n)
{
    zombies.push_back(n);
    n->setParent(this);
}
void GameScene::mousePressEvent(QMouseEvent *event)
{
    if (preparedPlant==""){
        for (int i=0;i<this->allsunshine.size();i++){
            //判断是否点到了阳光
            if (abs(this->allsunshine[i]->x+77/2-event->x())<=20 && abs(this->allsunshine[i]->y+77/2-event->y())<=30){
                allsunshine[i]->round=0;
                allsunshine[i]->fly();
                this->sunNum+=50;

            }
        }

        //判断是否点到了僵尸或植物，若是，展示攻击范围。
        for (int i=0;i<plants.size();i++){
            if ((event->x()-652)/105==plants[i]->y && (event->y()-173)/113==plants[i]->x){
                plants[i]->showAttackRange=1-plants[i]->showAttackRange;
                break;
            }
        }
        for (int i=0;i<zombies.size();i++){
            if (abs(event->x()-zombies[i]->x-50)<=40 && abs(event->y()-zombies[i]->y-50)<=40){
                zombies[i]->showAttackRange=1-zombies[i]->showAttackRange;
            }
        }
    }
    if (event->x()>=654 && event->x()<=1600 && event->y()>=174 && event->y()<=962){ //说明处在地图内

        int x=(event->x()-652)/105;
        int y=(event->y()-173)/113;
        if (preparedPlant=="nut"){
            if (map->scene[y][x]->landPath && !map->scene[y][x]->firstPlace && isPlaceEmpty(y,x)){
                qDebug()<<"成功种植nut";
                Nut * n = new Nut(y,x,100,":/res/nut.gif");
                createPlant(n);

                preparedPlant="";
            } else if (!isPlaceEmpty(y,x)) {
                Message * m = new Message(620,40,":/res/NotEmpty.png");
                m->setParent(this);
                if (this->currMess!=NULL){
                    this->currMess->close();
                    delete this->currMess;
                }
                this->currMess=m;
            } else if (!map->scene[y][x]->landPath){
                Message * m = new Message(620,40,":/res/MustOnGround.png");
                m->setParent(this);
                if (this->currMess!=NULL){
                    this->currMess->close();
                    delete this->currMess;
                }
                this->currMess=m;
            }
        }
        if (preparedPlant=="starfruit"){
            if (map->scene[y][x]->towerPos && isPlaceEmpty(y,x)){
                qDebug()<<"成功种植starfruit";
                StarFruit * n = new StarFruit(y,x,100,":/res/starfruitBullet.png");
                createPlant(n);
                preparedPlant="";
            } else if (!isPlaceEmpty(y,x)) {
                Message * m = new Message(620,40,":/res/NotEmpty.png");
                m->setParent(this);
                if (this->currMess!=NULL){
                    this->currMess->close();
                    delete this->currMess;
                }
                this->currMess=m;
            } else if (!map->scene[y][x]->towerPos){
                Message * m = new Message(620,40,":/res/MustOnLeaf.png");
                m->setParent(this);
                if (this->currMess!=NULL){
                    this->currMess->close();
                    delete this->currMess;
                }
                this->currMess=m;
            }
        }
        if (preparedPlant=="peashooter"){
            if (map->scene[y][x]->landPath && !map->scene[y][x]->firstPlace && isPlaceEmpty(y,x)){
                qDebug()<<"成功种植peashooter";
                //要判断来敌方向
                Peashooter * n;
                for (int i=0;i<map->landPaths.size();i++){
                    for (int j=0;j<map->landPaths[i].size()-1;j++){
                        if (map->landPaths[i][j+1]==map->scene[y][x]){//找到路径上当前位置的上一格
                            if (map->landPaths[i][j]->x==y && map->landPaths[i][j]->y==x-1){
                                qDebug()<<"豌豆射手向左！";
                                n = new Peashooter(y,x,100,":/res/peaBullet.png",0);

                            } else {
                                qDebug()<<"豌豆射手向右！";
                                n = new Peashooter(y,x,100,":/res/peaBullet.png",1);
                            }
                        }
                    }
                }

                createPlant(n);
                preparedPlant="";
            } else if (!isPlaceEmpty(y,x)) {
                Message * m = new Message(620,40,":/res/NotEmpty.png");
                m->setParent(this);
                if (this->currMess!=NULL){
                    this->currMess->close();
                    delete this->currMess;
                }
                this->currMess=m;
            } else if (!map->scene[y][x]->landPath){
                Message * m = new Message(620,40,":/res/MustOnGround.png");
                m->setParent(this);
                if (this->currMess!=NULL){
                    this->currMess->close();
                    delete this->currMess;
                }
                this->currMess=m;
            }
        }
        if (preparedPlant=="Spikeweed"){
            if (map->scene[y][x]->landPath && !map->scene[y][x]->firstPlace && isPlaceEmpty(y,x)){
                qDebug()<<"成功种植地刺";
                Spikeweed * s = new Spikeweed(y,x);
                createPlant(s);
                preparedPlant="";
            } else if (!isPlaceEmpty(y,x)) {
                Message * m = new Message(620,40,":/res/NotEmpty.png");
                m->setParent(this);
                if (this->currMess!=NULL){
                    this->currMess->close();
                    delete this->currMess;
                }
                this->currMess=m;
            } else if (!map->scene[y][x]->landPath){
                Message * m = new Message(620,40,":/res/MustOnGround.png");
                m->setParent(this);
                if (this->currMess!=NULL){
                    this->currMess->close();
                    delete this->currMess;
                }
                this->currMess=m;
            }
        }
        if (preparedPlant=="shovel"){
            preparedPlant="";
            for (int i=0;i<plants.size();i++){
                if (plants[i]->x==y && plants[i]->y==x){
                    plants[i]->isAlive=false;
                    plants[i]->currBlockUnits.clear();//其实清空与不清空都行，因为碰撞判定的前提是植物活着
                }
            }
        }


    } else if (preparedPlant!="") {
        Message * m = new Message(620,40,":/res/OutOfMap.png");
        m->setParent(this);
        if (this->currMess!=NULL){
            this->currMess->close();
            delete this->currMess;
        }
        this->currMess=m;

    }
    preparedPlant="";
}

void GameScene::judgeBlocked(Zombie* z)
{
    bool judge=false;//每轮僵尸的状态都必须更新，判断是否有成功更新。
    //因为有可能植物被铲了，导致没有植物存活，如果不是每轮更新僵尸状态，会出现bug
    for (int i=0;i<plants.size();i++){
        if (plants[i]->isAlive) {
            if ((z->getDirection()==1 && z->x==plants[i]->y*105+652 && z->y<=plants[i]->x*113+173+95 && z->y>=plants[i]->x*113+173+65)
                    || (z->getDirection()==2 && z->x==plants[i]->y*105+652 && z->y>=plants[i]->x*113+173-45 && z->y<=plants[i]->x*113+173-15)
                    || (z->getDirection()==3 && z->x<=plants[i]->y*105+652+50 && z->x>=plants[i]->y*105+652+20 && z->y==plants[i]->x*113+173)
                    || (z->getDirection()==4 && z->x>=plants[i]->y*105+652-45 && z->x<=plants[i]->y*105+652-15 && z->y==plants[i]->x*113+173)) {

                if (plants[i]->currBlockUnits.size()<plants[i]->getBlockUnits()) {
                    if (count(plants[i]->currBlockUnits.begin(),plants[i]->currBlockUnits.end(),z)==0){
                        plants[i]->currBlockUnits.push_back(z);
                    }
                    z->setBlocked(true);
                    judge=true;
                    break;
                }
            }
        }
    }
    if (!judge){
        z->setBlocked(false);
    }
}
bool GameScene::isPlaceEmpty(int x,int y)
{
    for (int i=0;i<plants.size();i++){
        if (plants[i]->x==x && plants[i]->y==y && plants[i]->isAlive){
            return false;
        }
    }
    return true;
}
void GameScene::lose()
{
    status=false;
    beforeGame->stop();
    timer->stop();
    timer2->stop();
    timer3->stop();
}
GameScene::~GameScene()
{
    delete player;
    delete playlist;
}
