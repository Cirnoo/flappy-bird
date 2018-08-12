#ifndef SCORE_H
#define SCORE_H
#include"myobject.h"
#include "scoreboard.h"
class Score:MyObject
{
public:
    Score();
    ~Score();
    void ScoreAdd();
    void ShowBoard();
    void ShowResult(QPainter &p);
private:
    void gameover();
    void frame();
    void restart();
    void show(QPainter &);
    void ShowNum(QPainter &,double x,double y,unsigned int num,QPixmap * Numimg);
    QPointer<ScoreBoard> board;
    unsigned int best=0,now=0;
};

#endif // SCORE_H
