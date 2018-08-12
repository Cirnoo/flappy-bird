
//#include "mylabel.h"

//MyLabel::MyLabel(QWidget *parent) :
//    QLabel(parent)
//    {
//    }

//    //鼠标释放事件
//    void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
//    {
//        if (ev->button() == Qt::LeftButton)
//            emit clicked();//(this);
//    }
//    //鼠标进入事件
//    void MyLabel::enterEvent(QEvent *)
//    {
//        this->setWindowOpacity(1);
//        QPixmap tempLogoPix = logoPix.scaled(imageWidth, imageHeight);
//        //如果可以旋转就启动定时器
//        if (isRotate){
//            rotateTimerId = startTimer(50);
//        }
//        //如果放大就设置图片发达1.5倍
//        if (isMagnify){
//            setImageSize(this->imageWidth*1.5, this->imageHeight*1.5);
//        }
//    }
//    //设置图片大小事件
//    void MyLabel::setImageSize(int imageWidth, int imageHeight)
//    {
//        this->imageWidth = imageWidth;
//        this->imageHeight = imageHeight;
//    }
//    void MyLabel::leaveEvent(QEvent *)
//    {
//    }
