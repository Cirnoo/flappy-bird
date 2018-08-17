#include"widget.h"
#include<QDesktopWidget>
#include<QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    // w.autoFillBackground();
    w.show();
    QIcon icon = QIcon(":/res/ico.ico");
    w.setWindowIcon(icon);
    w.move((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
