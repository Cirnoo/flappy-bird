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
    setFixedSize(288*RESOLUTION,512*RESOLUTION);
    view=QPixmap(this->size());
    init();
    this->grabKeyboard();
}

Widget::~Widget()
{
    for(int i=0;i<3;i++)
    {
        thread[i]->quit();
        thread[i]->wait();
    }
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
    for(int i=0;i<3;i++)
    {
        thread[i]=new QThread(this);
    }
    FrameThread->moveToThread(thread[0]);
    StateThread->moveToThread(thread[1]);
    thread[0]->start();
    thread[1]->start();
    timer.setInterval(13);
    timer.start();
    timer.setTimerType(Qt::PreciseTimer);
    connect(&timer, &QTimer::timeout, FrameThread,&MyThread::MyFrame);
    connect(this, &Widget::SendKeyPress, StateThread,&MyThread::MyKeyPress);
    connect(this, &Widget::Do, this,&Widget::frame2);
    connect(this,SIGNAL(SoundSig(int)), StateThread,SLOT(Sound(int)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

void Widget::frame2()
{
    DoFrame(InMainThread);
}

void Widget::paintEvent(QPaintEvent *)
{

    if(!update_flag)
        return;
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

}

void Widget::View()
{
    update();
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





