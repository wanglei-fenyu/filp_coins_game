#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include "mypushbutton.h"
#include <QLabel>
#include "mycoin.h"
#include "mydata.h"
#include <QPropertyAnimation>
#include <QSound>
#define cout qDebug() <<"["<<__FILE__<<":"<<__LINE__<<"]"
class Playscene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit Playscene(QWidget *parent = nullptr);
    Playscene(int index);
    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //记录关变量
    int leaveIndex;
    mydata *data;

    //金币或银币标志
    int gameArray[4][4];
    MyCoin *coinBtn[4][4];

    //是否胜利
    bool isWin;

signals:
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
