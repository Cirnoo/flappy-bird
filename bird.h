#ifndef BIRD_H
#define BIRD_H
#include"myobject.h"
#include<QQueue>
class Pipe;
class Bird : public MyObject
{
public:
    Bird();
    ~Bird();
    void keyPress();
    void Drop();
    volatile char state;
    QList<QPointer<Pipe>> pipelist;
private:
    QPixmap * ani=nullptr;
    unsigned int interval=20;
    int timer_key_delay=0;
    int timer_drop_delay=0;
    double rot_add=-1;
    double land;
    double g=0;
    double v_min=15;
    void frame();
    void gameover();
    void restart();
    void logic(const char);
    void fly();
    QPointer<Pipe> SetPipe(const double y) const ;
    void GameReady();
    void OnGameRun();
    bool IsColliGround() const ;
    void OnFly();
    void DelPipe();
    void GameOver();
    void StopPipe();
};

#endif // BIRD_H
