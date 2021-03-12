#include "choosselevelscene.h"

Choosselevelscene::Choosselevelscene(QWidget *parent) : QMainWindow(parent)
{   
    playscene = NULL;

    //设置固定大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置图片
    this->setWindowIcon(QIcon(":/n/src/Coin0001.png"));



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
    QSound *startSound1 = new QSound(":/n/src/BackButtonSound.wav",this);
    //添加一个返回按钮
    MyPushButton *backBtn = new MyPushButton(":/n/src/BackButton.png",":/n/src/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=]()
    {
        startSound1->play();
        //发送一个信号
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();
        });

    });

    //显示具体关卡
    QLabel *label = new QLabel;
    label->setParent(this);
    //创建一个字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //给label设置字体
    label->setFont(font);
    label->setText("请选择关卡！");
    label->setGeometry(QRect(30,this->height()-100,180,50));

    QSound *startSound = new QSound(":/n/src/TapButtonSound.wav",this);
    //startSound->setLoops(5); //设置循环

    //选择关卡按钮 20个
    for(int i=0;i<20;i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/n/src/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);

        /*设置按钮显示的内容*/
        QLabel *label = new QLabel(this);
        //设置标签大小
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        //设置显示内容
        label->setText(QString::number(i+1));
        //设置内容居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //移动位置
        label->move(25+(i%4)*70,130+(i/4)*70);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        //
        connect(menuBtn,&MyPushButton::clicked,[=]()
        {
            //cout << "您选择了第"<< i+1<<"关";
            //播放音效
            startSound->play();
            /*进入具体游戏场景*/
            //隐藏自己
            this->hide();
            playscene = new Playscene(i+1);
            playscene->setGeometry(this->geometry());
            playscene->show();
            connect(playscene,&Playscene::chooseSceneBack,[=]()
            {
                QTimer::singleShot(100,this,[=]()
                {
                    this->setGeometry(playscene->geometry());
                    //隐藏
                    playscene->close();
                    delete playscene;
                    playscene = NULL;
                    //显示
                    this->show();
                });
            });

        });
    }

}

void Choosselevelscene::paintEvent(QPaintEvent *)
{
    //画背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/n/src/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画标题
    QPixmap pix2(":/n/src/Title.png");
    pix2 = pix2.scaled(pix2.width(),pix2.height());
    painter.drawPixmap(10,30,pix2);
}
