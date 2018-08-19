#include "labelobj.h"

LabelObj::LabelObj(QPixmap _img)
{
    label.init(this,_img);
    img=&_img;
}

void LabelObj::MouseMove(bool flag)
{
    is_mouse_in=flag;
}

void LabelObj::frame()
{
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
    label.setPixmap(*img);
    label.setGeometry(x-buf.width(),y-buf.height(),buf.width(),buf.height());
}


