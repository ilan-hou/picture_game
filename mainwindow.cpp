#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QSound>
#include<QPaintEvent>
#include "gamewindow.h"
#include<windows.h>
#include"victory_dialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //111-lyh:为不规则窗口做准备部分
    this->setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
        //这个back_pic不能是指针类型的变量
    back_pic.load(":/image/back_1");//加载图像
    this->resize(back_pic.size());
    //111-lyh

    //56-lyh:音效相关
    bgm= new QSound(":/sound/sounds/Don't Let Your Guard Down.wav");
    bgm->play();
    //56

}

//117-lyh:为不规则窗口绘制背景:
void MainWindow::paintEvent(QPaintEvent event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, back_pic);//绘制图像
}
//lyh-117



//555-lyh:拖拽窗口相关:
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
      {  drag_menu = true;
        //获得鼠标的初始位置
        mouseStartPoint = event->globalPos();
        //mouseStartPoint = event->pos();
        //获得窗口的初始位置
        windowTopLeftPoint = this->frameGeometry().topLeft();

    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(drag_menu)
    {
        //获得鼠标移动的距离
        QPoint distance = event->globalPos() - mouseStartPoint;
        //QPoint distance = event->pos() - mouseStartPoint;
        //改变窗口的位置
        this->move(windowTopLeftPoint + distance);
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        drag_menu = false;
    }
}
//555-lyh

MainWindow::~MainWindow()
{
    delete ui;
}


//222-lyh点击开始按钮后的动作:
void MainWindow::on_btn_1_clicked()
{
//      QSoundEffect effect;
//      effect.setSource(QUrl::fromLocalFile("qrc:sound/sounds/btn_pressed.wav"));
//      effect.setLoopCount(1);
//      effect.setVolume(100);
//      effect.play();
    QSound::play(":/sound/sounds/page_change.wav");
    bgm->stop();



    if(game_window==NULL){
        game_window =new GameWindow();
        //155-lyh:退出按钮
        connect(game_window,&GameWindow::quit,[=](){
            show();
            bgm->play();
        });
        //155-lyh


    }
    this->close();
    game_window->start();
    game_window->show();
    game_window->bgm2->play();
    game_window->bgm2->setLoops(QSound::Infinite);
}
//222-lyh

//333-lyh:关闭程序相关
void MainWindow::on_btn_4_clicked()
{
    QSound::play(":/sound/sounds/btn_pressed.wav");
    this->hide();
    bgm->stop();

}
//333-lyh

//lyh_初始难度设置:
void MainWindow::on_btn_3_clicked()
{
     QSound::play(":/sound/sounds/btn_pressed.wav");
     Victory_Dialog *v =new Victory_Dialog();
     v->show();
}
