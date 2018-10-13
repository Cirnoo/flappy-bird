#include "backgroud.h"
#include "widget.h"
Back::Back(QPixmap& _img,double _y,double _v,int _layer)
{
    init(_img,_img.width()/2,_y,_v,0,_layer);
    x2=x+img->width()-1;

}

void Back::show(QPainter & p)
{
    p.drawPixmap(QPointF(x-img->width()/2,y-img->height()/2),*img);
    p.drawPixmap(QPointF(x2-img->width()/2,y-img->height()/2),*img);
}

void Back::frame()
{
    x+=vx;
    x2+=vx;
    if(x<=-img->width()/2)
    {
        x=img->width()/2;
        x2=x+img->width()-1;
    }
}

void Back::restart()
{
    task=true;
    if(layer==LAYER_BACK)
    {
        img=&sys->background[qrand()%2];
    }
}




