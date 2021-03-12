#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>

#define cout qDebug() <<"["<<__FILE__<<":"<<__LINE__<<"]"

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinImg); //参数:默认显示的金币还是银币
    void changeFlag();
    void mousePressEvent(QMouseEvent *e);



    int x;
    int y;
    bool flag;
    int min = 1;
    int max = 8;
    QTimer *time1;
    QTimer *time2;
    bool isAnimation;
    bool isWin;

signals:

};

#endif // MYCOIN_H
