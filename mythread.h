#ifndef MYTHREAD_H
#define MYTHREAD_H
#include"sys.h"
class Widget;
class MyThread : public QObject
{
    Q_OBJECT
public:
     MyThread();
    void MyFrame();//线程处理函数
    void MyKeyPress();
signals:

public slots:
    void Sound(int s);

protected:
    bool isStop=false;

};

#endif // MYTHREAD_H
