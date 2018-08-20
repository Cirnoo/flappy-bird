#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<mythread.h>
#include <QKeyEvent>
#include"mylabel.h"
#include<QDesktopWidget>
#include <QtGlobal>
#include <QTime>

Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(288*RESOLUTION,512*RESOLUTION);
    this->grabKeyboard();
    view=QPixmap(this->size());
    move((QApplication::desktop()->width() -width())/2,(QApplication::desktop()->height() - height())/2);
    QIcon icon = QIcon(":/res/ico.ico");
    setWindowIcon(icon);
    init();

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
    //extern int xxx;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    res.reset(new Res(this));
    tools.reset(new Tools());
    show();
    back.reset(new Back(res->background[qrand()%2],res->background[0].height()/2,-0.3,LAYER_BACK));
    ground.reset(new Back(res->ground,this->height()-res->ground.height()/2,-2,LAYER_GROUND));
    bird.reset(new Bird());
    socre .reset( new Score());
    for(int i=0;i<3;i++)
    {
        my_thread[i]=new MyThread();
        thread[i]=new QThread(this);
        my_thread[i]->moveToThread(thread[i]);
        thread[i]->start();
    }
    timer.setInterval(13);
    timer.start();
    timer.setTimerType(Qt::PreciseTimer);
    connect(&timer, &QTimer::timeout,my_thread[THREAD::FRAME],&MyThread::MyFrame);
    connect(this, &Widget::SendKeyPress,my_thread[THREAD::STATE],&MyThread::MyKeyPress);
    connect(this, &Widget::Do, this,&Widget::frame2);
    connect(this,SIGNAL(SoundSig(int)),my_thread[THREAD::SOUND],SLOT(Sound(int)));
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

void Widget::DoFrame(QMultiMap<int, MyObject*> & task_list)
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





