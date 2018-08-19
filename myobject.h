#ifndef MYOBJECT_H
#define MYOBJECT_H
#include"sys.h"
class Widget;
class MyObject : public QObject
{
public:
    explicit MyObject(QPixmap & _img, double _x=0, double _y=0, double _vx=0,double _vy=0, int _layer=0);
    MyObject();
    virtual void frame();
    virtual void show(QPainter &);
    virtual void gameover();
    virtual void restart();
    int layer=0;
    double rot=0;
    bool navi=false;
    int timer=0;
    QPixmap * img=nullptr;
    double vx=0,vy=0,x=0,y=0;
    bool hide=false;
    bool del_flag=false;
    bool task=true;
private:
protected:
    void init(QPixmap & _img,double _x,double _y,double _vx=0,double _vy=0,int _layer=0);
    void DefaultAction();

};
#endif
