#ifndef BACK_H
#define BACK_H
#include"myobject.h"
class Back : public MyObject
{
public:
    Back(QPixmap& _img,double _y,double _v,int _layer);
private:
    double x2;
    void show(QPainter & );
    void frame();
    void restart();
};

#endif // BACK_H
