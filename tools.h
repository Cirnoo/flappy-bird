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

    private:
        void frame();
        void gameover(){}
        void restart(){}
        QPixmap buf;
    };
    class Restart:public MyObject
    {
    public:
        Restart();
    friend class Tools;
    private:
        void frame();
        void gameover(){}
        void restart(){}
        QBitmap bit;
        unsigned char dead_time=60;
        bool ani_pause_flag=true;
    };
    class StartObject:public MyObject
    {
    public:
        StartObject();
        ~StartObject();
    private:
        void frame();
        void gameover(){}
        void restart(){}
        QPixmap buf;
    };
    bool IsAniPause();
    void Swap(double & ,double &);
    void SetBlink();
    void SetBlack();
    void SetLeader();
    void DrawPixmapAtCenter(double x,double y,QPixmap & img,QPainter & p);
    static QPixmap SetAlgha(QPixmap &,unsigned int algha);
private:
    QList<QPointer<MyObject>> objlist;
    QPointer<Restart> black_ani;
};

#endif // TOOLS_H
