#include "map.h"

Map::Map(QWidget *parent)
    : QWidget{parent}
{

}

Map::Map(QString p)
{
    QString path = QFileDialog::getOpenFileName(this,"选取地图文件",p);
    if (path==NULL){
        QMessageBox::critical(this,"警告","打开地图文件失败！");
    } else {
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QStringList parts=QString(file.readLine().trimmed()).split(" ");//去除换行符、用空格分割数据

        int Line=parts[0].toInt(),Row=parts[1].toInt();
        int i=0;

        file.readLine();
        vector<Place*> temp;
        for (int i=0;i<Line;i++){
            temp.clear();
            for (int j=0;j<Row;j++){
                parts=QString(file.readLine().trimmed()).split(" ");
                Place * place=new Place(parts[0].toInt(),parts[1].toInt(),parts[2].toInt(),parts[3].toInt(),parts[4].toInt(),parts[5].toInt());
                temp.push_back(place);

            }
            scene.push_back(temp);
        }
        file.readLine();
        int x,y;
        temp.clear();
        parts=QString(file.readLine().trimmed()).split(" ");


        x=parts[0].toInt();
        y=parts[1].toInt();
        scene[x][y]->firstPlace=true;
        temp.push_back(scene[x][y]);
        while (1){
            //读取陆地路径
            parts=QString(file.readLine().trimmed()).split(" ");
            if (parts[0]=="fly"){
                scene[x][y]->lastPlace=true;
                break;
            }
            if (parts[0]!="ground"){
                x=parts[0].toInt();
                y=parts[1].toInt();
                temp.push_back(scene[x][y]);
            } else {
                scene[x][y]->lastPlace=true;
                landPaths.push_back(temp);
                temp.clear();
            }

        }
        landPaths.push_back(temp);
        temp.clear();
        //读取天空路径
        parts=QString(file.readLine().trimmed()).split(" ");
        x=parts[0].toInt();
        y=parts[1].toInt();
        scene[x][y]->firstPlace=true;
        temp.push_back(scene[x][y]);
        while (!file.atEnd()){
            parts=QString(file.readLine().trimmed()).split(" ");
            if (parts[0]!="fly"){

                x=parts[0].toInt();
                y=parts[1].toInt();
                temp.push_back(scene[x][y]);
            } else {
                scene[x][y]->lastPlace=true;
                flyPaths.push_back(temp);
                temp.clear();
            }
        }
        scene[x][y]->lastPlace=true;
        flyPaths.push_back(temp);

    }
}

