#include<sys.h>
#include<QBitmap>
#include<QRgb>
#include<QColor>
#include"widget.h"
//QSound Res::s_fly(":/res/fly.wav");
Widget*  Res::User=nullptr;
Res::Res( Widget * p)
{
    User=p;
    back_temp=QPixmap(":/res/atlas.png");
    //back_temp.setMask(back_temp.createMaskFromColor(QColor(0,0,0),Qt::MaskInColor));
    back_temp=back_temp.scaled(back_temp.size()*RESOLUTION);
    nullimg=QPixmap(0,0);
    day_back=set(0,0,288,512);
    night_back=set(292,0,288,512);
    ground=set(584,0,336,112);
    for(int i=0;i<3;i++)
    {
        bird[0][i]=set(56*i,970,48,48);
    }
    game_ready=set(435,516,200,165);
    for(int i=0;i<10;i++)
    {
        num[0][i]=set(292+i%5*27,516+40*(i/5),27,40);
        num[1][i]=num[0][i].scaled(num[0][i].size()*0.5);
    }
    white=set(584,448,32,32);
    black=set(584,412,32,32);
    white=white.scaled(p->size());
    black=black.scaled(p->size()*1.5);
    pipe_down=set(112,646,52, 320);
    pipe_up=set(168,646,52, 320);
    game_over=set(784,116,204,54);
    score_board=set(0,516,238,126);
    button_play=set(702,234,116,70);
    back_temp=nullimg;
    QString temp [5]={"die","fly","hit","panel","point"};
    QString path=":/res/";
    for(int i=0;i<5;i++)
    {
        QString t=path+temp[i]+".wav";
        sound[i]=new QSound(t);
    }
}

QPixmap Res::set(int  x, int  y, int  w, int  h)
{
    return back_temp.copy(static_cast<int>(x*RESOLUTION),static_cast<int>(y*RESOLUTION)
                    ,static_cast<int>(w*RESOLUTION),static_cast<int>(h*RESOLUTION));
}



void DrawPixmapAtCenter(double x, double y, QPixmap &img, QPainter &p)
{
    p.drawPixmap(static_cast<int>(x-img.width()/2),static_cast<int>(y-img.height()/2),
                 img.width(),img.height(),img);
}
