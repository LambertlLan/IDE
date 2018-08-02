#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);//构造函数
    ~MainWindow();//析构函数
    void test();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
