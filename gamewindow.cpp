#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "victory_dialog.h"
GameWindow::GameWindow(QWidget *parent,int t,int s,int l) : QMainWindow(parent),
                                          ui(new Ui::GameWindow)
{
    time=t;
    size=s;
    level=l;
    ui->setupUi(this);
    timer->setInterval(10);//hrh:设置更新时间的间隔为10ms
    //118-lyh:为不规则窗口做准备部分
    this->setWindowFlags(Qt::FramelessWindowHint);    //设置窗体无边框
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明
        //这个back_pic不能是指针类型的变量
    back_pic.load(":/image/back_2"); //加载图像
    this->resize(back_pic.size());
    //118-lyh
    //yz
}
void GameWindow::start(){
    display_Time(time);
    ui->label_2->setText(QString("%1").arg(level));
    //hrh:将目标文件打乱
    switch (this->level) {
    case 1:reshuffle(":/image/images/1.jpg");
        break;
    case 2:reshuffle(":/image/images/2.jpg");
        break;
    case 3:reshuffle(":/image/images/3.jpg");
        break;
    case 4:reshuffle(":/image/images/4.jpg");
        break;
    case 5:reshuffle(":/image/images/5.jpg");
        break;
    }
    match_picLab();
};
//118-lyh:为不规则窗口绘制背景:
void GameWindow::paintEvent(QPaintEvent event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, back_pic); //绘制图像
}
void GameWindow::display_Time(double timeValue){
   QString leftTime=QString::number(timeValue, 'f', 3);
   QString usedTime=QString::number(usedTimeValue, 'f', 3);
    timer->start();
    //hrh:将QTimer的timeout信号与用于显示时间的槽连接
    connect(timer, &QTimer::timeout,[=]()mutable{
         ui->time_table->setText(usedTime);
         ui->timer_label->setText(leftTime);
         timeValue-=0.01;
         usedTimeValue+=0.01;
         if(timeValue>9.99 && timeValue <10.01){QSound::play(":/sound/sounds/warning.wav");}
         leftTime=QString::number(timeValue, 'f', 3);
         usedTime=QString::number(usedTimeValue, 'f', 3);
         if(fabs(timeValue)<0.001){
            timer->stop();
            timeOut=true;
          ui->timer_label->setText("0.000");
        }
    });
}
void  GameWindow::reshuffle(QString road){
    QPixmap target;
    target.load(road);
    int *order=new int [size*size];
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++){
             pictures.push_back(target.copy(i* (target.width() / size),  j * (target.height() / size),
                                target.width() / size , target.height() /size));
          }
    //建立序号和图片的键值对
    for(int i=0;i<size*size;i++){
        order[i]=i;
        imap[i]=pictures.at(i);
    }
    change=imap;
    unsigned seed = system_clock::now().time_since_epoch().count();//获取现在系统的时间戳来作为srand的种子
    srand(seed);
    //hrh:随机打乱
    while(change==imap){
for (int i = 50; i > 0; i--){
int index1=rand()%(size*size);
int index2=rand()%(size*size);
QPixmap temp;
temp=change[index1];
change[index1]=change[index2];
change[index2]=temp;
}
}
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
    {
            QLabel* label=new QLabel(this);
            label->setScaledContents(true);
            label->setGeometry(rect().x()+120+i*600 / size,
                               rect().y()+120+j*540 / size,
                               600/size,  540/size);
            label->setPixmap(change[size*i+j]);
            v_label.push_back(label);
    }

}
//lyh-118
GameWindow::~GameWindow()
{
    this->close();
    delete ui;
}

void GameWindow::victory(){
    QSound::play(":/sound/sounds/btn_pressed.wav");
   Victory_Dialog* vic=new Victory_Dialog();
     bgm2->stop();
     bgm3->play();
     connect(vic,&Victory_Dialog::home, [=]() {
                 emit quit();
                 this->hide();
             });
     connect(vic,&Victory_Dialog::again, [=]() {
         display_Time(time);
         //hrh:将目标文件打乱
         reshuffle(":/image/images/1.jpg");
         match_picLab();
             });
     connect(vic,&Victory_Dialog::next, [=]() {
         //118-lyh
              n++;
              GameWindow* game=new GameWindow(nullptr,n*60,2*n-1,n);
              game->start();
              game->show();
          });
     vic->show();
};
//155-lyh:退出按钮
void GameWindow::on_toolButton_clicked()
{
    QSound::play(":/sound/sounds/btn_pressed.wav");
    //559-lyh:退出对话框:
    Quit_Window *quit_dialog = new Quit_Window();
    bgm2->stop();
    //QSound::play(":/sound/sounds/dialog.wav");
    connect(quit_dialog, &Quit_Window::home, [=]() {
        emit quit();
        this->hide();
    });
    //999-lyh:这里是用来重来的
    connect(quit_dialog, &Quit_Window::home, [=]() {});
    //999-lyh
    quit_dialog->show();
    //559-lyh:
}
//155-lyh

//yz:图片与label匹配
void GameWindow::match_picLab()
{
    QList<QLabel *>::iterator lab_iter = v_label.begin();
    for (int i = 0; i <size *size; i++, lab_iter++)
    {
        (*lab_iter)->installEventFilter(this); //安装事件监听
    }
}

//yz:事件过滤器，捕捉鼠标点击图标事件，并调用交换图片函数swapPic
bool GameWindow::eventFilter(QObject *obj, QEvent *event) //
{
    bool isPic = 0; //isPic记录是否点击图片所在label
    //obj与v_Label中元素对比。若匹配：设置isPic及clickTime; picClicked数组记录被点击对象。
    if (((event->type()) != QEvent::MouseButtonPress) || ((obj->metaObject()->className()) != QStringLiteral("QLabel")))
    {
        return QObject::eventFilter(obj, event);
    }
    //qobj*转换为qlabel*类型
    QLabel *tmp = qobject_cast<QLabel *>(obj);
    QList<QLabel *>::iterator lab_iter = v_label.begin();
    for (int i = 0; i < size * size; i++, lab_iter++)
    {
        if (*lab_iter == tmp)
        {
            isPic = 1;
            picClicked[clickTime] = i;
            clickTime++;
            QSound::play(":/sound/sounds/coin.wav");
            break;
        }
    }
    //若已经点击2次：重置次数，判断是否相同图片，不同则调用交换函数swapPic
    if (clickTime == 2)
    {
        clickTime = 0;
        if (picClicked[0] != picClicked[1])
        {
            QSound::play(":/sound/sounds/swap.wav");
            swapPic(picClicked[0], picClicked[1]);
            step++;
        }
    }

    return QObject::eventFilter(obj, event);
}

//yz:交换图片
void GameWindow::swapPic(int a, int b)
{
    QPixmap temp;
    temp =change[a];
    change[a]=change[b];
    change[b]=temp;
    QList<QLabel *>::iterator lab_iter = v_label.begin();
    for (int i = 0; i < size * size; i++, lab_iter++)
    {
        (*lab_iter)->setPixmap(change[i]);
    }
    if(change==imap){
       v_label.clear();
       usedTimeValue=0;
       timer->stop();
       victory();
//      this->close();
//     GameWindow* game=new GameWindow();
//     game->time=30;
//     game->level=2;
//     game->size=3;
//     game->show();
//     game->start();
    }
}
