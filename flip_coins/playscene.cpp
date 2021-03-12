#include "playscene.h"

Playscene::Playscene(int index)
{
    //cout<<"第"<<index<<"关开始";
    this->leaveIndex = index;

    //设置固定大小
    this->setFixedSize(320,588);
    //设置标题
    QString str;
    str = QString("第%1关").arg(this->leaveIndex);
    this->setWindowTitle(str);
    //设置图片
    this->setWindowIcon(QIcon(":/n/src/Coin0001.png"));

    isWin = false;
    QSound *startSounda = new QSound(":/n/src/ConFlipSound.wav",this);
    QSound *startSoundb = new QSound(":/n/src/LevelWinSound.wav",this);
    //创建菜单栏
    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    //创建菜单项
    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=]()
    {
        this->close();
    });

    //添加一个返回按钮
    QSound *startSound1 = new QSound(":/n/src/BackButtonSound.wav",this);
    MyPushButton *backBtn = new MyPushButton(":/n/src/BackButton.png",":/n/src/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=]()
    {
        startSound1->play();
        //发送一个信号
        emit this->chooseSceneBack();
    });

    //显示具体关卡号
    QString str1 = QString("Leave: %1").arg(this->leaveIndex);
    QLabel *label = new QLabel;
    label->setParent(this);
    //创建一个字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //给label设置字体
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(QRect(30,this->height()-100,150,50));

    data = new mydata;
    data->setParent(this);
    //初始化游戏中的二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j] = data->mData[this->leaveIndex][i][j];
        }
    }

    //创建胜利下砸
    QLabel * winLabel = new QLabel;
    QPixmap pix;
    pix.load(":/n/src/LevelCompletedDialogBg.png");
    winLabel->setGeometry(QRect(0,0,pix.width(),pix.height()));
    winLabel->setParent(this);
    winLabel->setPixmap(pix);
    winLabel->move((this->width() - pix.width())*0.5,-pix.height());

    //创建金币的背景图片
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel * bg = new QLabel(this);
            bg->setGeometry(0,0,50,50);
            bg->setPixmap(QPixmap(":/n/src/BoardNode(1).png"));
            bg->move(57+i*50,200+j*50);

            QString str;
            if(this->gameArray[i][j] == 1)
            {
                str = ":/n/src/Coin0001.png";
            }
            else
            {
                str = ":/n/src/Coin0008.png";
            }
            //创建金币
            MyCoin *coin = new MyCoin(str);
            coin->x = i;
            coin->y = j;
            coin->flag = this->gameArray[i][j];
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coinBtn[i][j] = coin;
            //将coin放入维护的金币的二维数组
            connect(coin,&MyCoin::clicked,[=]()
            {
                startSounda->play();
                //翻自己
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j]==0 ? 1 : 0;//同步二维数组
                //翻周围
                QTimer::singleShot(200,this,[=]()
                {
                    //检测翻右侧
                    if(coin->x+1 <= 3)
                    {
                        coinBtn[coin->x+1][coin->y]->changeFlag();
                        gameArray[coin->x+1][coin->y] = gameArray[coin->x+1][coin->y] == 0 ? 1 : 0;
                    }
                    //检测翻左侧
                    if(coin->x-1 >= 0)
                    {
                        coinBtn[coin->x-1][coin->y]->changeFlag();
                        gameArray[coin->x-1][coin->y] = gameArray[coin->x-1][coin->y] == 0 ? 1 : 0;
                    }
                    //检测翻下
                    if(coin->y+1 <= 3)
                    {
                        coinBtn[coin->x][coin->y+1]->changeFlag();
                        gameArray[coin->x][coin->y+1] = gameArray[coin->x][coin->y+1] == 0 ? 1 : 0;
                    }
                    //检测翻上
                    if(coin->y-1 >= 0)
                    {
                        coinBtn[coin->x][coin->y-1]->changeFlag();
                        gameArray[coin->x][coin->y-1] = gameArray[coin->x][coin->y-1] == 0 ? 1 : 0;
                    }

                    isWin = true;
                    //翻完一次判断是否全为金币
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        startSoundb->play();
                        //游戏胜利
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        //将胜利的图片显示出来
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+188,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });

        }
    }
}

void Playscene::paintEvent(QPaintEvent *)
{
    //画背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/n/src/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画标题
    QPixmap pix2(":/n/src/Title.png");
    pix2 = pix2.scaled(pix2.width()*0.5,pix2.height()*0.5);
    painter.drawPixmap(10,30,pix2);
}
