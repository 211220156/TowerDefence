#ifndef PLACE_H
#define PLACE_H

#include <QWidget>
#include <QVector>
using std::vector;

class Place : public QWidget
{
    Q_OBJECT
public:
    explicit Place(QWidget *parent = nullptr);
    Place(bool landPath,bool flyPath,bool towerPos,bool forbidden,int x,int y);

    bool isLandPath();
    bool isFlyPath();
    bool isTowerPos();
    bool isForbidden();
    bool firstPlace=false;
    bool lastPlace=false;
    int getX();
    int getY();

    bool landPath;
    bool flyPath;
    bool towerPos;
    bool forbidden;
    int x;
    int y;


signals:

};

#endif // PLACE_H
