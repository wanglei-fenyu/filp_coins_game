#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //点击退出，退出游戏
    connect(ui->actionquit,&QAction::triggered,[=]()
    {
        this->close();
    });

    //设置固定大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币");
    //设置图片
    this->setWindowIcon(QIcon(":/n/src/Coin0001.png"));
    //设置start按钮
    MyPushButton *startBtn = new MyPushButton(":/n/src/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.7);

    //准备按钮音效
    QSound *startSound = new QSound(":/n/src/TapButtonSound.wav",this);
    //startSound->setLoops(5); //设置循环
    //创建第二个场景
    chossScene = new Choosselevelscene;
    connect(startBtn,&MyPushButton::clicked,[=]()
    {
        //cout << "start按下了";
        //点击start执行的效果
        //播放
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入第二个场景
        QTimer::singleShot(300,this,[=]()
        {
            //先将自身隐藏
            this->hide();

            //设置窗口位置
            chossScene->setGeometry(this->geometry());

            //进入下第二个场景
            chossScene->show();
        });

    });

    connect(chossScene,&Choosselevelscene::chooseSceneBack,[=]()
    {
        QTimer::singleShot(200,this,[=]()
        {
            //隐藏选择窗口
            chossScene->hide();
            this->setGeometry(chossScene->geometry());

            //显示主窗口
            this->show();
        });
    });
}

void MainWindow::paintEvent(QPaintEvent *)
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

MainWindow::~MainWindow()
{
    delete ui;
}

