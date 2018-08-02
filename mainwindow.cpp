#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#define cout qDebug()

//构造函数,主要做初始化工作
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    test();

}

//如果需要封装函数,函数内部需要使用ui控件,此函数必须为结构体(类)中的函数
//类中声明,类外定义,定义时加上作用域
void MainWindow::test(){
    cout << "MainWindow";
    //给标签设置内容
    ui->label->setText("Hello QT");
    //获取标签的内容
    QString str = ui->label->text();

    cout<< "str =" << str;
    //QTextEdit操作
    ui->textEdit->setText("hello mike");
    //获取编辑区的内容
    QString textStr = ui->textEdit->toPlainText();

    cout << "textStr=" << textStr;
}

//析构函数,对象结束前(窗口关闭前),自动调用,做一些清理工作
MainWindow::~MainWindow()
{
    delete ui;
}
