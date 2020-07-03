#include "victory_dialog.h"
#include "ui_victory_dialog.h"
#include<QSound>
Victory_Dialog::Victory_Dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Victory_Dialog)
{
    ui->setupUi(this);

    //11-lyh:为不规则窗口做准备部分
        this->setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框
        this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
//        back_picture.load(":image/back_1");
//        this->resize(back_picture.size());
        //11-lyh
    QSound::play(":/sound/sounds/victory_fireworks.wav");
    QSound::play(":/sound/sounds/victory_jingle.wav");
    QSound::play(":/sound/sounds/victory_screen_start.wav");

}
//11-lyh:为不规则窗口绘制背景:
void Victory_Dialog::paintEvent(QPaintEvent event){
//    Q_UNUSED(event);
//    QPainter painter(this);
//    painter.drawPixmap(0, 0, back_picture);//绘制图像
}
//lyh-11

Victory_Dialog::~Victory_Dialog()
{
    delete ui;
}

//89-lyh:重来按钮
void Victory_Dialog::on_toolButton_clicked()
{
    QSound::play(":/sound/sounds/btn_pressed.wav");
    emit again();
    this->close();
}
//89-lyh

//77-lyh:关闭 按钮
void Victory_Dialog::on_toolButton_3_clicked()
{

    QSound::play(":/sound/sounds/btn_pressed.wav");
    emit next();
    this->close();
}
//77-lyh

//22-lyh:home按钮
void Victory_Dialog::on_toolButton_2_clicked()
{
    QSound::play(":/sound/sounds/btn_pressed.wav");
    emit home();
    this->close();
}
//22-lyh:home按钮
