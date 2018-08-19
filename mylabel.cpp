#include "mylabel.h"
#include"labelobj.h"
MyLabel::MyLabel()
{

}

MyLabel::~MyLabel()
{

}


void MyLabel::init(LabelObj * _obj, QPixmap &image)
{
    obj=_obj;
    setPixmap(image);
    resize(buf.width(),buf.height());
}



void MyLabel::enterEvent(QEvent *)
{
   obj->MouseMove(true);
}

void MyLabel::leaveEvent(QEvent *)
{
    obj->MouseMove(false);
}



void MyLabel::mousePressEvent(QMouseEvent * event)
{
}

