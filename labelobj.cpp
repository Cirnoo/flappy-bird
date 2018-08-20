#include "labelobj.h"
#include "widget.h"
LabelObj::LabelObj(QPixmap _img)
{
    img=&_img;
    Res::User->AddToMainThread(this,_img);
    timer=-1;
}

LabelObj::~LabelObj()
{
    if(label)
    {
        delete label;
    }
}

void LabelObj::MouseMove(bool flag)
{
    is_mouse_in=flag;
}

void LabelObj::frame()
{
    if(timer++==-1)
    {
        label=new MyLabel;
        label->init(this,*img);
    }
    if(is_mouse_in==true)
    {
        timer=timer<10?timer+1:10;
    }
    else
    {
        timer=timer>0?timer-1:0;
    }
    if(timer>0)
    {
       buf=img->scaled(img->size()*(1+timer*0.15));
    }
    label->setPixmap(*img);
    label->setGeometry(x-buf.width(),y-buf.height(),buf.width(),buf.height());
}




