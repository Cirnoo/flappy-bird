#include "mythread.h"
#include "widget.h"
MyThread::MyThread()
{

}

void MyThread::MyFrame()
{
    Res::User->frame();
}

void MyThread::MyKeyPress()
{
    Res::User->bird->keyPress();
}

void MyThread::Sound(int s)
{
    Res::User->res->sound[s]->play();
}

