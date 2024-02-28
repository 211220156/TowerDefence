#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QVector>
#include "place.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <string>
#include <QMessageBox>
using std::vector;
class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    Map(QString p);

    vector<vector<Place*>> scene;
    vector<vector<Place*>> landPaths;
    vector<vector<Place*>> flyPaths;

signals:

};

#endif // MAP_H
