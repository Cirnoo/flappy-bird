#include "tools.h"
#include"widget.h"
#include <QPainter>
Tools::Tools()
{

}

Tools::~Tools()
{
    for(auto i:objlist)
    {
        if(!i.isNull())
        {
            delete i;
        }
    }
}


void Tools::Swap(double & a, double & b)
{
    double temp=a;
    a=b;
    b=temp;
}

void Tools::SetBlink()
{
    objlist.push_back(new Blink());
}

void Tools::SetBlack()
{
    objlist.push_back(new Restart());
}

void Tools::SetLeader()
{
    objlist.push_back((new StartObject()));
}

void Tools::DrawPixmap(double x,double y,QPixmap& img,QPainter &p)
{
    p.drawPixmap(static_cast<int>(x-img.width()/2),static_cast<int>(y-img.height()/2),
                 img.width(),img.height(),img);
}




QPixmap Tools::SetAlgha(QPixmap &img, unsigned int algha)
{
    QPixmap output(img.size());
    output.fill(Qt::transparent);
    QPainter p(&output);
    p.setOpacity(algha/255.0);
    p.drawPixmap(0, 0, img);
    p.end();
    return  output;
}

Tools::Blink::Blink()
{
    Res::User->AddToMainThread(this,Res::User->res->nullimg,Res::User->width()/2,y=Res::User->height()/2);
}

void Tools::Blink::frame()
{
    buf=SetAlgha(Res::User->res->white,170-15*(3-timer)*(3-timer));
    img=&buf;
    if(++timer==6)
    {
        del_flag=true;
    }

}

Tools::Restart::Restart()
{

    black=Res::User->res->black;
    bit=black;
    init(bit,Res::User->width()/2,Res::User->height()/2,0,0,LAYER_TOP);
}

void Tools::Restart::frame()
{
    if(flag)
    {
        if(timer>30&&timer<60)
        {
            timer++;
            return;
        }
        else if(timer>60)
        {
            flag=false;
            timer=31;
        }
    }
    int r=((timer-dead_time/2)*(timer-dead_time/2)*static_cast<unsigned int>(bit.width())/1800);
    bit=black;
    img=&black;
    QPainter p;
    p.begin(&bit);
    QBrush brush(Qt::color0);
    p.setBrush(brush);
    p.drawEllipse(QPoint(bit.width()/2,bit.height()/2),r,r);
    p.end();
    img->setMask(bit);
    if(++timer==dead_time)
    {
        del_flag=true;
    }
}


Tools::StartObject::StartObject()
{
    Res::User->AddToMainThread(this,Res::User->res->game_ready,Res::User->width()/2,y=Res::User->height()/2-70);
}

Tools::StartObject::~StartObject()
{
    //qDebug()<<"obj delete ok";
}

void Tools::StartObject::frame()
{
    if(Res::User->bird->state!=0)
    {
        buf=SetAlgha(Res::User->res->game_ready,255-5*timer++);
        img=&buf;
        if(timer==50)
        {
            del_flag=true;
            //qDebug()<<GetCurrentThreadId();
        }
    }
}
