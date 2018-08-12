#ifndef SYS_H
#define SYS_H
#include<QPainter>
#include <QtMath>
#include<QtCore/QObject>
#include<QTimer>
#include<QMultiMap>
#include<QApplication>
#include<QDebug>
#include <QBitmap>
#include <QThread>
#include <QGLWidget>
#include <QScopedPointer>
#include<QPointer>
#include <QList>
#define RESOLUTION 1.5
#define COLLI_SIZE 9
#define LAYER_BACK 0
#define LAYER_PIPE 100
#define LAYER_GROUND 200
#define LAYER_PLAYER 300
#define LAYER_LABEL 400
#define LAYER_TOP 500
class Widget;

class Res
{
public:

   Res(Widget* p);
   static Widget*  User;
   QPixmap nullimg,day_back,night_back,ground,bird[3][3],game_ready,num[2][10],white,black,pipe_down,pipe_up,
           game_over,score_board,button_play ;
private:
   QPixmap set(int  ,int ,int  ,int );
   QPixmap back_temp;
};
#endif // SYS_H
