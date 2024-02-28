#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include "map.h"
#include "gamescene.h"
#include "beginbutton.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
extern GameScene * game;
class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Map* map;
    int gameLevel=0;
    void paintEvent(QPaintEvent *event);
    QMediaPlayer * player;
    QMediaPlaylist * playlist;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
