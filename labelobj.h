#ifndef LABELOBJ_H
#define LABELOBJ_H
#include"mylabel.h"
#include"myobject.h"
class LabelObj :public MyObject
{
    Q_OBJECT
public:
    LabelObj(QPixmap _img);
    ~LabelObj();
    void MouseMove(bool);
private:
    MyLabel* label;
    void frame();
    void show(QPainter &){}
    void restart();
    bool is_mouse_in=false;
    QPixmap buf;
signals:
    void newobj();
};




#endif // LABELOBJ_H
