#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<mythread.h>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(430,768);
    view=QPixmap(430,760);
    init();
    this->grabKeyboard();
}

Widget::~Widget()
{
    thread1->quit();
    thread1->wait();
    thread2->quit();
    thread2->wait();
    delete ui;
}

void Widget::AddToSubThread(int layer, MyObject * obj)
{

    InSubThread.insert(layer,obj);
}
void Widget::AddToMainThread(MyObject * obj,QPixmap & img,double x,double y)
{
    obj->img=&img;
    obj->x=x;
    obj->y=y;
    InMainThread.insert(LAYER_TOP,obj);
}

void Widget::init()
{
    res.reset(new Res(this));
    tools.reset(new Tools());
    back.reset(new Back(res->day_back,res->day_back.height()/2,-0.3,LAYER_BACK));
    ground.reset(new Back(res->ground,this->height()-res->ground.height()/2,-2,LAYER_GROUND));
    bird.reset(new Bird());
    socre .reset( new Score());
    FrameThread = new MyThread();
    StateThread = new MyThread();
    thread1 = new QThread(this);
    thread2 = new QThread(this);
    FrameThread->moveToThread(thread1);
    thread1->start();
    thread2->start();
    timer.setInterval(12);
    timer.start();
    timer.setTimerType(Qt::PreciseTimer);
    connect(&timer, &QTimer::timeout, FrameThread,&MyThread::MyFrame);
    connect(this, &Widget::SendKeyPress, StateThread,&MyThread::MyKeyPress);
    connect(this, &Widget::Do, this,&Widget::frame2);
    connect(&timer, &QTimer::timeout, StateThread,&MyThread::MyView);
}

void Widget::frame2()
{
    DoFrame(InMainThread);
}

void Widget::paintEvent(QPaintEvent *)
{

    if(!update_flag)
        return;

    QPainter painter2(this);
    painter2.drawPixmap(rect(),view);
    update_flag=false;
}

void Widget::GameOver()
{
    for(auto i:InSubThread)
    {
        i->gameover();
    }
}

void Widget::ReStart()
{
    for(auto i:InSubThread)
    {
        i->restart();
    }
}


void Widget::frame()  //每帧执行
{
    timer_count++;
    DoFrame(InSubThread);

    if(!InMainThread.empty())
    {
        emit Do();
    }
    update_flag=true;
    update();
}

void Widget::View()
{
    QPainter painter(&view);
    for(auto i:InSubThread)
    {
        if(!i->hide)
        {
            i->show(painter);
        }
    }
    for(auto i:InMainThread)
    {
        if(!i->hide)
        {
            i->show(painter);
        }
    }

}
void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space)
    {
        emit SendKeyPress();
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    emit SendKeyPress();
}

void Widget::DoFrame(QMultiMap<int, QPointer<MyObject>> & task_list)
{
    auto i=task_list.begin();
    while (i!=task_list.end())
    {
        if((*i)->del_flag)
        {
            delete (*i);
            i=task_list.erase(i);
        }
        else
        {
           if((*i)->task)
           {
               (*i)->frame();
           }
           i++;
        }
    }
}





