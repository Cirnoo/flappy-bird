#include"widget.h"
#include<QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    // w.autoFillBackground();
    w.show();
    w.move((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
