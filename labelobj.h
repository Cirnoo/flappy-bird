#ifndef LABELOBJ_H
#define LABELOBJ_H
#include"mylabel.h"
#include"myobject.h"
class LabelObj :public MyObject
{
public:
    LabelObj(QPixmap _img);
    ~LabelObj(){}
    void MouseMove(bool);
private:
    MyLabel label;
    void frame();
    void show(QPainter &){}
    bool is_mouse_in=false;
    QPixmap buf;
};



#endif // LABELOBJ_H
