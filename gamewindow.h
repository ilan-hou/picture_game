#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include<QSound>
#include <QMainWindow>
#include "victory_dialog.h"
#include "quit_window.h"
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include<QSound>
#include<QTimer>
#include <chrono>
#include <map>
using std::chrono::system_clock;
using std::map;
namespace Ui
{
    class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0,int t=60,int s=2,int l=1);
    ~GameWindow();


    //118-lyh:不规则窗体部分
    QPixmap back_pic;
    void reshuffle(QString road);
    void start();
    void paintEvent(QPaintEvent);
    //118-lyh
    void display_Time(double timeValue);
    //77-lyh:胜利部分对话框
    //Victory_Dialog *victory_dialog=NULL;
    //77-lyh

    //lyh:音效部分:
    QSound *bgm2=new QSound(":/sound/sounds/on_game~1.wav") ;
    QSound *bgm3=new QSound(":/sound/sounds/victory_jingle.wav") ;
    //hrh:记录步数的变量
    int step=0;
    //hrh:记录是否超时的变量
    bool timeOut=false;
    //hrh:记录是否超出步数的变量
    bool stepOut=false;
    int level=0;
    //hrh:记录已用时间的变量
    double usedTimeValue=0;
    QList<QPixmap> pictures;
    bool warning=false;
    map<int,QPixmap> imap,change;
    int size = 0; //难度
    int time=0;
    QTimer* timer = new QTimer();
    //yz:图片对应label构成的队列
    QList<QLabel *> v_label;
    void victory();

    //yz:记录两次点击的图片,图片序号从0开始
    int picClicked[2];
    //yz:记录点击图片次数
    int clickTime = 0;
    //yz:图片与label匹配
    void match_picLab();
    //yz:事件过滤器，捕捉鼠标点击图标事件，并调用交换图片函数swapPic
    bool eventFilter(QObject *obj, QEvent *event);
    //yz:交换图片
    void swapPic(int, int);

    //155-lyh:退出按钮
public:
signals:
    void quit();
    //155-lyh
private slots:
    void on_toolButton_clicked();

private:
    Ui::GameWindow *ui;
    static int n;
};

#endif // GAMEWINDOW_H
