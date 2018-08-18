#ifndef SYS_H
#define SYS_H
#include<QPainter>
#include <QtMath>
#include<QtCore/QObject>
#include<QDebug>
#include <QBitmap>
#include <QScopedPointer>
#include<QPointer>
#include <QList>
#include <QSound>


const double RESOLUTION = 1.5  ;
const int COLLI_SIZE =     9   ;
const int LAYER_BACK =     0   ;
const int LAYER_PIPE =   100   ;
const int LAYER_GROUND = 200   ;
const int LAYER_PLAYER = 300   ;
const int LAYER_LABEL =  400   ;
const int LAYER_TOP =    500   ;


namespace MYSOUND
{
    enum  {DIE=0,FLY,HIT,PANEL,POINT};
}
namespace THREAD
{
    enum {FRAME=0,STATE,SOUND};
}
namespace STATE
{
    enum {START,RUN,DROP,OVER,RESTART};
}

class Widget;
class Res
{
public:
   Res(Widget* p);
   static Widget*  User;
   QPixmap nullimg,day_back,night_back,ground,bird[3][3],game_ready,num[2][10],white,black,pipe_down,pipe_up,
           game_over,score_board,button_play ;
   QPointer<QSound> sound[5];
private:

   QPixmap set(int  ,int ,int  ,int );
   QPixmap back_temp;
};
void DrawPixmapAtCenter(double x,double y,QPixmap& img,QPainter &p);
#endif // SYS_H
