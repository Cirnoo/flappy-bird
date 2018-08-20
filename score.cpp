#include "score.h"
#include"widget.h"
Score::Score()
{
    auto & p=Res::User;
    img=Res::User->res->num[0];
    x=p->width()/2;y=120;
    layer=LAYER_PLAYER;
    p->AddToSubThread(layer,this);

}

Score::~Score()
{
    if(!board.isNull())
    {
        delete board;
    }
}

void Score::frame()
{

    return;
}

void Score::restart()
{
    now=0;
}

void Score::show(QPainter &p)
{
    ShowNum(p,x,y,now,img);
}

void Score::ShowNum(QPainter & p, double x, double y,unsigned int num,QPixmap * Numimg)
{
    if(num==0)
    {
        DrawPixmapAtCenter(x,y,*Numimg,p);
    }
    unsigned int temp=num;
    int count=-1;
    while (temp>0)
    {
        count++;
        DrawPixmapAtCenter(x-count*Numimg->width(),y,*(Numimg+temp%10),p);
        temp/=10;
    }
}



void Score::ScoreAdd()
{
    now++;
    emit Res::User->SoundSig(MYSOUND::POINT);
}

void Score::ShowBoard()
{
    board=(new ScoreBoard);
}

void Score::ShowResult(QPainter &p)
{
    unsigned int temp=now*board->timer2/30;
    ShowNum(p,board->x_board+120,board->y_board-24,temp,img+10);
    ShowNum(p,board->x_board+120,board->y_board+32,best,img+10);
}

bool Score::IsFinish()
{
    return board->timer>160;
}

void Score::gameover()
{
     best=qMax(best,now);
}


