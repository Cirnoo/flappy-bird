#ifndef WIDGET_H
#define WIDGET_H
#include"myobject.h"
#include"back_groud.h"
#include"bird.h"
#include"tools.h"
#include"pipe.h"
#include"score.h"
namespace Ui {
class Widget;
}
class MyThread;
class Widget : public QGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void AddToSubThread(int,MyObject*);
    void AddToMainThread(MyObject * obj,QPixmap & img,double x=0,double y=0);
    QScopedPointer<Res> res;
    QScopedPointer<Tools>  tools;
    unsigned int timer_count=0;
    QScopedPointer<Back> ground;
    QScopedPointer<Bird>  bird;
    QScopedPointer<Score>  socre;
    void GameOver();
    void ReStart();
public slots:
    void frame();
    void View();
signals:
    void SendKeyPress();
    void Do();
private:
    void init();
    void frame2();
    QTimer timer;
    QScopedPointer<Back> back;
    QMultiMap<int,QPointer<MyObject>> InSubThread;
    QMultiMap<int,QPointer<MyObject>> InMainThread;
    void paintEvent(QPaintEvent *);
    Ui::Widget *ui;
    MyThread * FrameThread;
    MyThread * StateThread;
    QThread *thread1;
    QThread *thread2;
    QPixmap view;
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent * event);
    bool update_flag=false;
    void DoFrame(QMultiMap<int,QPointer<MyObject>> &);
};


#endif // WIDGET_H
