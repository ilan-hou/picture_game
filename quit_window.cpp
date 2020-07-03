#include "quit_window.h"
#include "ui_quit_window.h"
#include<QSound>
Quit_Window::Quit_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Quit_Window)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
}

Quit_Window::~Quit_Window()
{
    delete ui;
}

//889-lyh:按下home按钮的槽函数:
void Quit_Window::on_toolButton_2_clicked()
{
    QSound::play(":/sound/sounds/btn_pressed.wav");
    emit home();
    this->close();
    QSound::play(":/sound/sounds/page_change.wav");
}
//889-lyh


//555-lyh:按下重来按钮:
void Quit_Window::on_toolButton_clicked()
{
    QSound::play(":/sound/sounds/btn_pressed.wav");
    emit again();
    this->close();
}
//555-lyh
