#ifndef MYLABEL_H
#define MYLABEL_H
#include<QLabel>
#include<QMouseEvent>
class LabelObj;
class MyLabel : public QLabel
{
    Q_OBJECT
public:
        MyLabel();
        ~MyLabel();
public:
        void init(LabelObj* ,QPixmap & image);
signals:
private:
        LabelObj * obj;
        QPixmap buf;
        bool is_mouse_in=false;
        void mousePressEvent(QMouseEvent *);
        void enterEvent(QEvent *);
        void leaveEvent(QEvent *);
        //定时器

};

#endif // MYLABEL_H
