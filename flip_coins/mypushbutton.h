#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#define cout qDebug() <<"["<<__FILE__<<":"<<__LINE__<<"]"
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;

    //向上跳跃
    void zoom1();
    //向下跳跃
    void zoom2();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标松开事件
    void mouseReleaseEvent(QMouseEvent *e);
signals:


};

#endif // MYPUSHBUTTON_H
