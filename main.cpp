#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;//调用构造函数
    w.show();


    //a.exec()类似于死循环,让程序(窗口不结束),等待用户操作
    return a.exec();
}
