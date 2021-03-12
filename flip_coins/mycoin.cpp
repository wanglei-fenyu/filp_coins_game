#include "mycoin.h"

MyCoin::MyCoin(QString coinImg)
{
    QPixmap pix;
    bool ret = pix.load(coinImg);
    if(!ret)
    {
        QString str = QString("图片加载失败 %1").arg(coinImg);
        QMessageBox::critical(this,"加载失败",str);
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    //设置边框
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    time1 = new QTimer(this);
    time2 = new QTimer(this);
    this->isAnimation = false;
    isWin = false;

    //监听定时器
    connect(time1,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString str = QString(":/n/src/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        //设置边框
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min > this->max)
        {
            this->min = 1;
            time1->stop();
            this->isAnimation = false;
        }
    });
    connect(time2,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString str = QString(":/n/src/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        //设置边框
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max < this->min)
        {
            this->max = 8;
            time2->stop();
            this->isAnimation = false;
        }
    });
}

//改变标志执行翻转效果
void MyCoin::changeFlag()
{
    this->isAnimation = true;
    if(this->flag)
    {
        this->flag = false;
        time1->start(30);
    }
    else
    {
        this->flag = true;
        time2->start(30);
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        //交给父类
        QPushButton::mousePressEvent(e);
    }
}
