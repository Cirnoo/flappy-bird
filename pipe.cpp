#include "pipe.h"
#include "widget.h"


Pipe::Pipe(double _y)
{
    init(sys->pipe_up,sys->GetMainWidget()->width()+150,_y,sys->GetMainWidget()->ground->vx,0,LAYER_PIPE);
    space=150;
    y_up=_y+space+sys->pipe_down.height();
}

void Pipe::frame()
{
    if(CheckColli())
    {
        sys->GetMainWidget()->tools->SetBlink();
        sys->GetMainWidget()->bird->Drop();
        sys->GetMainWidget()->GameOver();
    }
    else
    {
        DefaultAction();
        if(colli&&x+img->width()/2<sys->GetMainWidget()->bird->x)
        {
            sys->GetMainWidget()->socre->ScoreAdd();
            colli=false;
        }
        if(del_flag)
        {
            sys->GetMainWidget()->bird->pipelist.pop_front();
        }
    }
}

void Pipe::show(QPainter &p)
{
    QPixmap & p1=sys->pipe_down;
    QPixmap & p2=sys->pipe_up;
    DrawPixmapAtCenter(x,y,p1,p);
    DrawPixmapAtCenter(x,y_up,p2,p);
}

void Pipe::gameover()
{
    task=false;
    colli=false;
}

void Pipe::restart()
{
    del_flag=true;
}

bool Pipe::CheckColli()
{
    auto & bird=sys->GetMainWidget()->bird;
    if(bird->x+COLLI_SIZE>x-img->width()/2&&
       bird->x-COLLI_SIZE<x+img->width()/2&&
       (bird->y-COLLI_SIZE<y+img->height()/2||
       bird->y+COLLI_SIZE>y_up-img->height()/2))
    {
       return true;
    }
    return false;
}
