#include "bird.h"
#include "widget.h"
#include "pipe.h"

using namespace STATE;
Bird::Bird()
{

    restart();
    init(*img,130,sys->GetMainWidget()->height()/2-50,0,1,LAYER_PLAYER);
    land=sys->GetMainWidget()->height()-sys->ground.height()-21;
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
    else if(sys->GetMainWidget()->socre->IsFinish())
    {
        task=true;
        sys->GetMainWidget()->tools->SetBlack();

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

void Bird::logic(const char state)
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
        if(sys->GetMainWidget()->tools->IsAniPause())
        {
            sys->GetMainWidget()->ReStart();
        }
        break;
    default:

        break;
    }
}

void Bird::fly()
{
    emit sys->GetMainWidget()->SoundSig(MYSOUND::FLY);
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
    x=130;y=sys->GetMainWidget()->height()/2-50;
    state=START;
    ani=sys->bird[qrand()%3];
    sys->GetMainWidget()->tools->SetLeader();
}


QPointer<Pipe> Bird::SetPipe(const double y) const
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
    if(timer%130==0)
    {
       pipelist.push_back(SetPipe(qrand()%239-150));
    }
}

bool Bird::IsColliGround() const
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
    g=(vy<4)?((vy<0)?0.21:0.33):0.42;
    if(IsColliGround())
    {
        if(state==RUN)
        {
           sys->GetMainWidget()->GameOver();
           sys->GetMainWidget()->tools->SetBlink();
           emit sys->GetMainWidget()->SoundSig(MYSOUND::HIT);
        }
        state=OVER;
        return;
    }
    else if(state==DROP)
    {
        timer_drop_delay++;
        if(timer_drop_delay==40)
        {
            emit sys->GetMainWidget()->SoundSig(MYSOUND::DIE);
        }
    }

}



void Bird::Drop()
{
    state=DROP;
    vy=-1;
    g=0.35;
    interval=0;
    emit sys->GetMainWidget()->SoundSig(MYSOUND::HIT);
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
    sys->GetMainWidget()->socre->ShowBoard();
    task=false;
    state=RESTART;
}



