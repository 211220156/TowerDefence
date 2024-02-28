#ifndef SUNSHINE_H
#define SUNSHINE_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
class sunshine : public QLabel
{
    Q_OBJECT
public:
    explicit sunshine(QWidget *parent = nullptr);

    sunshine(int x,int y,int targetY);
    QTimer * timer;
    int x;
    int y;
    int targetY;
    int catched=false;
    int disappeared=false;
    int round=0;
    void fly();
    ~sunshine();

signals:

};

#endif // SUNSHINE_H
