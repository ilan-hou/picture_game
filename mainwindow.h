#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSoundEffect>
#include <QMainWindow>
#include"gamewindow.h"
#include<QSound>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //117-lyh:不规则窗体部分
    QPixmap back_pic;
    void paintEvent(QPaintEvent);
    //117-lyh

    //555-lyh:这些和拖拽窗口有关:
    bool drag_menu;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //555-lyh

    //222-lyh游戏界面:
    GameWindow *game_window=NULL;
private slots:
    void on_btn_1_clicked();
    void on_btn_4_clicked();
    //222-lyh

    //56-lyh:音效相关
    void on_btn_3_clicked();

public:   QSound *bgm=NULL;
    //56



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
