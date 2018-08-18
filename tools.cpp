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

bool Tools::IsAniPause()
{
    return !black_ani.isNull()&&black_ani->timer>31;
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
    auto temp=new Restart();
    objlist.push_back(temp);
    black_ani=temp;
}


void Tools::SetLeader()
{
    objlist.push_back((new StartObject()));
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
    buf=Res::User->res->nullimg;
    init(buf,Res::User->width()/2,Res::User->height()/2,0,0,LAYER_TOP);
}

void Tools::Blink::frame()
{
    if(++timer==4)
    {
        del_flag=true;
    }
}



void Tools::Blink::show(QPainter & p)
{
     buf=SetAlgha(Res::User->res->white,170-15*(3-timer)*(3-timer));
     p.drawPixmap(0,0,buf);
}



Tools::Restart::Restart()
{
    bit=Res::User->res->black;
    init(Res::User->res->nullimg,Res::User->width()/2,Res::User->height()/2,0,0,LAYER_TOP);
}

void Tools::Restart::frame()
{
    if(ani_pause_flag)
    {
        if(timer>30&&timer<=50)
        {
            timer++;
            return;
        }
        else if(timer>50)
        {
            ani_pause_flag=false;
            timer=31;
        }
    }
    r=(timer-dead_time/2)*(timer-dead_time/2)*bit.width()/1200;
    if(++timer==dead_time)
    {
        del_flag=true;
    }
}

void Tools::Restart::show(QPainter & p)
{
    bit=Res::User->res->black;
    QPainter painter;
    painter.begin(&bit);
    QBrush brush(Qt::color0);
    painter.setBrush(brush);
    painter.drawEllipse(QPoint(bit.width()/2,bit.height()/2),r,r);
    painter.end();
    bit.setMask(bit);
    p.drawPixmap(QPointF(x-bit.width()/2,y-bit.height()/2),bit);
}

Tools::StartObject::StartObject()
{
    init(Res::User->res->game_ready,Res::User->width()/2,y=Res::User->height()/2-70,0,0,LAYER_TOP);
}



void Tools::StartObject::frame()
{
    if(Res::User->bird->state!=0)
    {
        img=&buf;
        if(timer++==50)
        {
            del_flag=true;
        }
    }

}

void Tools::StartObject::show(QPainter & p)
{
    buf=SetAlgha(Res::User->res->game_ready,255-5*timer);
    DrawPixmapAtCenter(x,y,buf,p);
}
