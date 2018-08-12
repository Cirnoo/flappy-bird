#ifndef TOOLS_H
#define TOOLS_H
#include"myobject.h"

class Tools
{

public:
    Tools();
    ~Tools();
    class Blink:public MyObject
    {
    public:
        Blink();
        void frame();
    private:
        QPixmap buf;
    };
    class Restart:public MyObject
    {
    public:
        Restart();
        void frame();
        QBitmap bit,black;
    private:
        unsigned char dead_time=60;
        bool flag=1;
    };
    class StartObject:public MyObject
    {
    public:
        StartObject();
        ~StartObject();
        void frame();
    private:
        QPixmap buf;
    };
    void Swap(double & ,double &);
    void SetBlink();
    void SetBlack();
    void SetLeader();
    void DrawPixmap(double x,double y,QPixmap & img,QPainter & p);
    static QPixmap SetAlgha(QPixmap &,unsigned int algha);
private:
    QList<QPointer<MyObject>> objlist;
};

#endif // TOOLS_H
