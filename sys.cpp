#include"sys.h"
#include<QBitmap>
#include<QRgb>
#include<QColor>
#include"widget.h"
Global * sys;
Global::Global()
{
    ResInit();
}

void Global::SetMainWidget(Widget * const p)
{
    user=p;
}

Widget *Global::GetMainWidget() const
{
    return user;
}

void Global::ResInit()
{
    back_temp=QPixmap(":/res/atlas.png");
    QSize window_size=QSize(WINDOW_WHITH,WINDOW_HEIGHT);
    back_temp=back_temp.scaled(back_temp.size()*RESOLUTION);
    nullimg=QPixmap(0,0);
    background[0]=set(0,0,288,512);
    background[1]=set(292,0,288,512);
    ground=set(584,0,336,112);
    for(int i=0;i<3;i++)
    {
        bird[0][i]=set(56*i,970,48,48);
        bird[1][i]=set(224,646+52*i,48,48);
        bird[2][i]=set(224,646+52*(i+3),48,48);
    }
    game_ready=set(435,516,200,165);
    for(int i=0;i<10;i++)
    {
        num[0][i]=set(292+i%5*27,516+40*(i/5),27,40);
        num[1][i]=num[0][i].scaled(num[0][i].size()*0.5);
    }
    white=set(584,448,32,32);
    black=set(584,412,32,32);
    white=white.scaled(window_size);
    black=black.scaled(window_size);
    pipe_down=set(112,646,52, 320);
    pipe_up=set(168,646,52, 320);
    game_over=set(784,116,204,54);
    score_board=set(0,516,238,126);
    button_play=set(702,234,116,70);
    for(int i=0;i<4;i++)
    {
        medals[i]=set(294,748-48*i,48,46);
    }
    new_record=set(224,1002,32,14);
    back_temp=nullimg;
    QString temp [5]={"die","fly","hit","panel","point"};
    QString path=":/res/";
    for(int i=0;i<5;i++)
    {
        QString t=path+temp[i]+".wav";
        sound[i]=new QSound(t);
    }
}

QPixmap Global::set(int  x, int  y, int  w, int  h)
{
    return back_temp.copy(static_cast<int>(x*RESOLUTION),static_cast<int>(y*RESOLUTION)
                    ,static_cast<int>(w*RESOLUTION),static_cast<int>(h*RESOLUTION));
}



void DrawPixmapAtCenter(double x, double y, QPixmap &img, QPainter &p)
{
    p.drawPixmap(static_cast<int>(x-img.width()/2),static_cast<int>(y-img.height()/2),
                 img.width(),img.height(),img);
}
