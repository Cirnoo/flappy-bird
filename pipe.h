#ifndef PIPE_H
#define PIPE_H
#include "myobject.h"

class Pipe:MyObject
{
public:
    Pipe(double _y);
    //void TaskStop();
private:
    void frame();
    void show(QPainter & p);
    bool colli=true;
    int space;
    double y_up;
    bool CheckColli();
};

#endif // PIPE_H
