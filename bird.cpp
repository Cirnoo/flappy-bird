#include "bird.h"
#include "widget.h"
#include "pipe.h"

using namespace STATE;
Bird::Bird()
{

    restart();
    init(*img,130,Res::User->height()/2-50,0,1,LAYER_PLAYER);
    land=Res::User->height()-Res::User->res->ground.height()-21;
    state=START;
}

Bird::~Bird()
{
    DelPipe();
}

void Bird::keyPress()
{
    if(task)
    {
        if(timer_key_delay<=10||y<20)
        {
            return;
        }
        timer_key_delay=0;
        if(state==START)
        {
            state=RUN;
        }
        if(state==RUN)
        {
            fly();
        }
    }
    else if(Res::User->socre->IsFinish())
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
       y=y<land?y:land;
       vy=qMin(v_min,vy+g);
       timer_key_delay++;
}

void Bird::logic(char state)
{
    switch (state)
    {
    case START:
        GameReady();
        break;
    case RUN:
        OnGameRun();
        break;
    case DROP:
        OnFly();
        break;
    case OVER:
        GameOver();
        break;
    case RESTART:
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
    emit Res::User->SoundSig(MYSOUND::FLY);
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
    timer_key_delay=0;
    timer_drop_delay=0;
    timer=0;
    x=130;y=Res::User->height()/2-50;
    state=START;
    ani=Res::User->res->bird[qrand()%3];
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
        rot=(vy>5)?rot-4.5:(vy>4)?rot-2.5:(vy>3)?rot-1:rot;
    }
    rot=(rot<-89)?-90:rot;
    if(vy>2)
    {
        interval=0;
    }
    g=(vy<4)?((vy<0)?0.2:0.33):0.4;
    if(IsColliGround())
    {
        if(state==RUN)
        {
           Res::User->GameOver();
           Res::User->tools->SetBlink();
           emit Res::User->SoundSig(MYSOUND::HIT);
        }
        state=OVER;
        return;
    }
    else if(state==DROP)
    {
        timer_drop_delay++;
        if(timer_drop_delay==40)
        {
            emit Res::User->SoundSig(MYSOUND::DIE);
        }
    }

}



void Bird::Drop()
{
    state=DROP;
    vy=-1;
    g=0.35;
    interval=0;
    emit Res::User->SoundSig(MYSOUND::HIT);
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
    state=RESTART;
}



