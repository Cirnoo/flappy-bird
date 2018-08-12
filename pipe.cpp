#include "pipe.h"
#include "widget.h"


Pipe::Pipe(double _y)
{
    init(Res::User->res->pipe_up,Res::User->width()+150,_y,Res::User->ground->vx,0,LAYER_PIPE);
    space=150;
    y_up=_y+space+Res::User->res->pipe_down.height();
}

void Pipe::frame()
{
    if(CheckColli())
    {
        Res::User->tools->SetBlink();
        Res::User->bird->Drop();
        Res::User->GameOver();
    }
    else
    {
        DefaultAction();
        if(colli&&x+img->width()/2<Res::User->bird->x)
        {
            Res::User->socre->ScoreAdd();
            colli=false;
        }
        if(del_flag)
        {
            Res::User->bird->pipelist.pop_front();
        }
    }
}

void Pipe::show(QPainter &p)
{
    QPixmap & p1=Res::User->res->pipe_down;
    QPixmap & p2=Res::User->res->pipe_up;
    Res::User->tools->DrawPixmapAtCenter(x,y,p1,p);
    Res::User->tools->DrawPixmapAtCenter(x,y_up,p2,p);
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
    auto & bird=Res::User->bird;
    if(bird->x+COLLI_SIZE>x-img->width()/2&&
       bird->x-COLLI_SIZE<x+img->width()/2&&
       (bird->y-COLLI_SIZE<y+img->height()/2||
       bird->y+COLLI_SIZE>y_up-img->height()/2))
    {
       return true;
    }
    return false;
}
