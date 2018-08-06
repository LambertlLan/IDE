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

private slots:
    void on_actionopen_triggered();

    void on_actionutf_8_triggered();

    void on_actiongbk_triggered();


    void on_actionsave_as_triggered();

    void on_actionundo_triggered();

    void on_actioncopy_triggered();

    void on_actionpaste_triggered();

    void on_actioncut_triggered();

    void on_actioncompile_triggered();

    void on_actionsave_triggered();

    void code_save(char *ch_path);

    void on_actionexit_triggered();

    void on_actionnew_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
