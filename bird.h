#ifndef BIRD_H
#define BIRD_H
#include"myobject.h"
#include<QQueue>
class Pipe;
class Bird : public MyObject
{
public:
    Bird(QPixmap* _img,double _x,double _y,double _v,int _layer);
    void keyPress();

    void GameOver();
    char state;
    QQueue<Pipe*> pipelist;
private:
    QPixmap * ani=nullptr;
    QPointer<MyObject> start;
    unsigned int interval=20;
    unsigned int timer2=0;
    double rot_add=-1;
    int land;
    double g=0;
    double v_min=15;
    void frame();
    void gameover();
    void logic(char);
    void fly();
    Pipe * SetPipe(double y);
    void GameReady();
    void OnGameRun();
    bool IsColliGround();
    void OnFly();
    void Drop();
};

#endif // BIRD_H
