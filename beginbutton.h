#ifndef BEGINBUTTON_H
#define BEGINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QPropertyAnimation>
class beginButton : public QPushButton
{
    Q_OBJECT
public:
    explicit beginButton(QWidget *parent = nullptr);

    beginButton(QString normalImg,QString pressImg="");

    QString normalImgPath;
    QString pressedImgPath;

    void zoom1();
    void zoom2();

signals:

};

#endif // BEGINBUTTON_H
