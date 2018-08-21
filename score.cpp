#include "score.h"
#include"widget.h"
Score::Score():new_record(Res::User->res->new_record)
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
    new_record_flag=false;
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

void Score::ShowMedals(QPainter & p)
{
    if(now/10>0)
    {
        DrawPixmapAtCenter(board->x_board-0.28*board->board.width(),board->y_board+7,
                           Res::User->res->medals[now<50?now/10-1:3],p);
    }
    if(new_record_flag)
    {
        DrawPixmapAtCenter(board->x_board+0.15*board->board.width(),board->y_board+0.15*board->board.height(),
                           Res::User->res->new_record,p);
    }
}



void Score::ScoreAdd()
{
    now++;
    if(now>best)
    {
        new_record_flag=true;
    }
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
    if(board->timer2>=30)
    {
        ShowMedals(p);
    }
}

bool Score::IsFinish()
{
    return board->timer>160;
}

void Score::gameover()
{
     best=qMax(best,now);
}


