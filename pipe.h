#ifndef PIPE_H
#define PIPE_H
#include "myobject.h"

class Pipe:public MyObject
{
public:
    Pipe(double _y);
    //void TaskStop();
private:
    void frame();
    void show(QPainter & p);
    void gameover();
    void restart();
    bool colli=true;
    int space;
    double y_up;
    bool CheckColli();
};

#endif // PIPE_H
