#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include"myobject.h"

class ScoreBoard:public MyObject
{
public:
    ScoreBoard();
    friend class Score;
private:
    void frame();
    void show(QPainter &);
    void gameover();
    unsigned int timer2=0;
    QPixmap over;
    QPixmap play;
    QPixmap * board;
    int x_over,y_over,x_board,y_board,x_play,y_play;//over和board坐标
};

#endif // SCOREBOARD_H
