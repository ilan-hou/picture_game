#ifndef QUIT_WINDOW_H
#define QUIT_WINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
namespace Ui {
class Quit_Window;
}

class Quit_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Quit_Window(QWidget *parent = 0);
    ~Quit_Window();

public :signals:
    //点击重来发送的信号
    void again();
    //点击home'发送的信号
    void home();

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::Quit_Window *ui;
};

#endif // QUIT_WINDOW_H
