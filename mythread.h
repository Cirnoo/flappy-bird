#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
class Widget;
class MyThread : public QObject
{
    Q_OBJECT
public:
     MyThread();
    void MyFrame();//线程处理函数
    void MyKeyPress();
    void MyView();
signals:

public slots:


protected:
    bool isStop=false;

};

#endif // MYTHREAD_H
