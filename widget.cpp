#include "widget.h"
#include "./ui_widget.h"
#include "map.h"
#include "place.h"
#include <QLabel>
#include <QMenuBar>
#include <QtCore>
GameScene * game=NULL;
Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置主场景
//    setMouseTracking(true);
    //播放音乐
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("C:\\Users\\86139\\Desktop\\TowerDenfence\\res\\bgm1.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);//循环播放
    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->setVolume(30);
    player->play();


    setFixedSize(1920,1080);
    setWindowIcon(QIcon(":/res/mainWidgetIcon.png"));
    setWindowTitle("TowerDenfence");
    QMenuBar * bar = menuBar();
    //将菜单栏放入窗口
    setMenuBar(bar);

    //创建菜单
    QMenu * choice = bar->addMenu("选项");

    QAction * createMap = choice->addAction("导入地图");
    QAction * quit = choice->addAction("退出游戏");

    QMenu * level = bar->addMenu("设置");
    QAction * difficult = level->addAction("困难");
    QAction * middle = level->addAction("中等");
    QAction * easy = level->addAction("简单");

    connect(quit,&QAction::triggered,this,[=](){
        this->close();
    });

    connect(difficult,&QAction::triggered,this,[=](){
        this->gameLevel=2;
    });

    connect(middle,&QAction::triggered,this,[=](){
        this->gameLevel=1;
    });

    connect(easy,&QAction::triggered,this,[=](){
        this->gameLevel=0;
    });

    beginButton * startBtn = new beginButton(":/res/startBtn.png");
    startBtn->setParent(this);
    startBtn->move(700,800);
    connect(startBtn,&QPushButton::clicked,this,[=](){
        //触发特效
        startBtn->zoom1();
        startBtn->zoom2();
    });
    connect(createMap,&QAction::triggered,this,[=](){
        this->map= new Map("C:\\Users\\86139\\Desktop");//修改对应路径，导入地图文件。
        if (!this->map->scene.empty()){
            connect(startBtn,&QPushButton::clicked,this,[=](){
                //延迟0.5后 进入游戏
                game = new GameScene(this->map,this->gameLevel);
                QTimer::singleShot(500,this,[=](){
                    this->hide();
                    player->stop();
                    game->show();
                });
            });
        } else {
            delete this->map;
        }
    });



}
void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap pixmap(":/res/background.png");
    pixmap = pixmap.scaled(1920,1080, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0,0,pixmap);

    //设置标题
    painter.drawPixmap(150,300,QPixmap(":/res/title.png"));

}

Widget::~Widget()
{
    delete player;
    delete playlist;
    delete ui;
}

