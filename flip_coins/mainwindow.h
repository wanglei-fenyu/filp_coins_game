#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "choosselevelscene.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

#define cout qDebug() <<"["<<__FILE__<<":"<<__LINE__<<"]"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //绘图事件
    void paintEvent(QPaintEvent *);
    Choosselevelscene *chossScene;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
