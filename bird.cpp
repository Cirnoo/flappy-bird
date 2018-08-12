#include "bird.h"
#include "widget.h"
#include "pipe.h"
#include <QtGlobal>
#include <QTime>
Bird::Bird()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    restart();
    init(*img,130,Res::User->height()/2-50,0,1,LAYER_PLAYER);
    land=Res::User->height()-Res::User->res->ground.height()-21;

}

Bird::~Bird()
{
    DelPipe();
}

void Bird::keyPress()
{
    if(timer2<=10||y<20)
    {
        return;
    }
    timer2=0;
    if(task)
    {
        if(state==0)
        {
            state=1;

        }
        if(state==1)
        {
            fly();
        }
    }
    else
    {
        task=true;
        Res::User->tools->SetBlack();

    }
}

void Bird::StopPipe()
{
    for(auto i:pipelist)
    {
        i->task=false;
    }
}

void Bird::frame()
{
       img=(interval)?(ani+timer/interval%3):(ani+1);
       logic(state);
       DefaultAction();
       y=qMin(y,land);
       vy=qMin(v_min,vy+g);
       timer2++;
}

void Bird::logic(char state)
{
    switch (state)
    {
    case 0:
        GameReady();
        break;
    case 1:
        OnGameRun();
        break;
    case 2:
        OnFly();
        break;
    case 3:
        GameOver();
        break;
    case 4:
        if(Res::User->tools->IsAniPause())
        {
            Res::User->ReStart();
        }
        break;
    default:

        break;
    }
}

void Bird::fly()
{

    vy=-6.5;
    interval=5;
    rot_add=(rot>0)?3:(25-rot)/12.0;
}

void Bird::gameover()
{
    return;
}

void Bird::restart()
{
    rot=0;
    vy=1;
    interval=20;
    timer2=0;
    timer=0;
    x=130;y=Res::User->height()/2-50;
    state=0;
    ani=Res::User->res->bird[0];
    Res::User->tools->SetLeader();
}


QPointer<Pipe> Bird::SetPipe(double y)
{
    return new Pipe(y);
}

void Bird::GameReady()
{
    vy=1.0*qCos(timer/23.0);
}

void Bird::OnGameRun()
{
    OnFly();
    if(timer%150==0)
    {
       pipelist.push_back(SetPipe(qrand()%239-150));
    }
}

bool Bird::IsColliGround()
{
    if(y>=land)
    {
        return true;
    }
    return false;
}

void Bird::OnFly()
{
    if(rot_add>=0)
    {
        (rot<25)?(rot+=rot_add):rot_add=-1;rot=25;
    }
    else
    {
        rot=(vy>5)?rot-4.5:(vy>4)?rot-3.5:(vy>3)?rot-1:rot;
    }
    rot=(rot<-89)?-90:rot;
    if(vy>2)
    {
        interval=0;
    }
    g=(vy<4)?((vy<0)?0.2:0.33):0.4;
    if(IsColliGround())
    {
        if(state==1)
        {
           Res::User->GameOver();
           Res::User->tools->SetBlink();
        }
        state=3;
        return;
    }
}



void Bird::Drop()
{
    state=2;
    vy=-1;
    g=0.35;
    interval=0;

}

void Bird::DelPipe()
{
    for(auto i:pipelist)
    {
        if(!i.isNull())
        {
            delete i;
        }
    }
    pipelist.clear();
}

void Bird::GameOver()
{
    Res::User->socre->ShowBoard();
    task=false;
    state=4;
}



