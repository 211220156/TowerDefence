#ifndef MESSAGE_H
#define MESSAGE_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
class Message : public QLabel
{
    Q_OBJECT
public:
    explicit Message(QWidget *parent = nullptr);
    Message(int x,int y,QString path);
    QTimer * timer;
    bool active;
    int x,y;

signals:

};

#endif // MESSAGE_H
