#include "myobject.h"
#include "widget.h"
MyObject::MyObject(QPixmap & _img, double _x, double _y, double _vx,double _vy, int _layer)
{
    init(_img,_x,_y,_vx,_vy,_layer);
}

MyObject::MyObject()
{

}


void MyObject::init(QPixmap & _img, double _x,double _y,double _vx,double _vy,int _layer)
{

    timer=0;
    img=&_img;
    x=_x;
    y=_y;
    vx=_vx;
    vy=_vy;
    layer=_layer;
    Res::User->AddToSubThread(layer,this);

}

void MyObject::show(QPainter & p)
{
    p.translate(x,y);
    p.rotate(-rot);
    p.drawPixmap(QPoint(-img->width()/2,-img->height()/2),*img);
    p.resetTransform();
}

void MyObject::gameover()
{
    task=false;
}

void MyObject::restart()
{
    task=true;
}


void MyObject::DefaultAction()
{
    timer++;
    x+=vx; y+=vy;
    if(x<-50)
        del_flag=true;

}

void MyObject::frame()
{
    DefaultAction();
}




