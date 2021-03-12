#ifndef CHOOSSELEVELSCENE_H
#define CHOOSSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include "mypushbutton.h"
#include <QLabel>
#include <QTimer>
#include <QSound>
#define cout qDebug() <<"["<<__FILE__<<":"<<__LINE__<<"]"

class Choosselevelscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit Choosselevelscene(QWidget *parent = nullptr);
    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //选着关卡维护一个游戏场景的指针
    Playscene *playscene;
signals:
    void chooseSceneBack();

};

#endif // CHOOSSELEVELSCENE_H
