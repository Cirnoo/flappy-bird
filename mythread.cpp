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

void MyThread::MyView()
{
    Res::User->View();
}

