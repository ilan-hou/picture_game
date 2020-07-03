#ifndef VICTORY_DIALOG_H
#define VICTORY_DIALOG_H

#include <QMainWindow>
#include<QPainter>
#include<QPaintEvent>
#include<QPixmap>
#include<QSoundEffect>
namespace Ui {
class Victory_Dialog;
}

class Victory_Dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit Victory_Dialog(QWidget *parent = 0);
    ~Victory_Dialog();

public :signals:
    //点击重来发送的信号
    void again();
    //点击home'发送的信号
    void home();
    //点击下一关发送的信号:
    void next();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_2_clicked();

private:
    //11-lyh:不规则窗体部分
    QPixmap back_picture;
    void paintEvent(QPaintEvent);
    //11-lyh


private:
    Ui::Victory_Dialog *ui;
};

#endif // VICTORY_DIALOG_H
