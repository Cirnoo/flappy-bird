#include "mythread.h"
#include "widget.h"
MyThread::MyThread()
{

}

void MyThread::MyFrame()
{
    sys->GetMainWidget()->frame();
}

void MyThread::MyKeyPress()
{
    sys->GetMainWidget()->bird->keyPress();
}

void MyThread::Sound(int s)
{
    sys->sound[s]->play();
}

