#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QTextCodec>

#define cout qDebug()

QTextCodec *codec;
QString path;

enum Mycode
{
    utf_8,gbk
};

enum Mycode flag;
//构造函数,主要做初始化工作
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //flag默认为utf_8;
    flag = utf_8;

    codec = QTextCodec::codecForName("GBK");

    test();

}

//如果需要封装函数,函数内部需要使用ui控件,此函数必须为结构体(类)中的函数
//类中声明,类外定义,定义时加上作用域
void MainWindow::test(){
    cout << "MainWindow";
    //给标签设置内容
    ui->label->setText("当前为UTF-8编码");
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
/**
 * @brief MainWindow::on_actionopen_triggered
 * 打开文件
 */
void MainWindow::on_actionopen_triggered()
{
    //1.打开一个文件,获取文件目录
    path = QFileDialog::getOpenFileName();
    if(path.isEmpty()){
        return;
    }
    //2.由于通过QT获取的路径,此路径为utf-8编码
    //同时将QString 转化为 char *
    const char * filename = codec->fromUnicode(path).data();
    //3.打开文件,fopen(),fopen()如果是中文,需要gbk
    FILE *fp = fopen(filename,"rb");
    if(fp == NULL){
        cout << "打开文件失败";
        return;
    }
    //4.循环读取文件的内容,fgets(),读取的内容是char *
    char buf[1024];
    QString str="";
    while(1){
        memset(buf,0,sizeof(buf));
        fgets(buf,sizeof(buf),fp);
        cout << buf;
        //判断当前需要显示的编码
        if(flag == utf_8){
            str += buf;
        }else if(flag == gbk){
            str += codec->toUnicode(buf);
        }
        if(feof(fp)){
            break;
        }
    }
    //5.需要把读取的内容给编辑区设置setText
    ui->textEdit->setText(str);
    //6.关闭文件
    fclose(fp);

}

/**
 * @brief MainWindow::on_actionutf_8_triggered
 * 切换为utf-8编码
 */
void MainWindow::on_actionutf_8_triggered()
{
    flag = utf_8;
    ui->label->setText("当前为UTF-8编码");
    cout << "flag = " << flag;
}
/**
 * @brief MainWindow::on_actiongbk_triggered
 * 切换为gbk编码
 */
void MainWindow::on_actiongbk_triggered()
{
    flag = gbk;
    ui->label->setText("当前为GBK编码");
    cout << "flag = " << flag;
}
/**
 * @brief MainWindow::on_actionsave_as_triggered
 * 另存为功能
 */
void MainWindow::on_actionsave_as_triggered()
{
    //1.选择一个保存文件的路径,这个路径从QT得到,是utf-8
    path = QFileDialog::getSaveFileName();
    //2.需要将utf-8转换为gbk,同时将QString转换为char *
    char * ch_path = codec->fromUnicode(path).data();
    code_save(ch_path);

}
/**
 * @brief MainWindow::on_actionundo_triggered
 * 撤销功能
 */
void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}
/**
 * @brief MainWindow::on_actioncopy_triggered
 * 复制
 */
void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}
/**
 * @brief MainWindow::on_actionpaste_triggered
 * 粘贴
 */
void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}
/**
 * @brief MainWindow::on_actioncut_triggered
 * 剪切
 */
void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}
/**
 * @brief MainWindow::on_actioncompile_triggered
 * 编译
 */
void MainWindow::on_actioncompile_triggered()
{
    //先保存文件
    on_actionsave_triggered();
    //再编译文件
    QString compile_path = path;
    compile_path.replace(".c",".exe");
    QString cmd = QString("gcc %1 -o %2").arg(path).arg(compile_path);
    system(codec->fromUnicode(cmd).data());
    QString run_cmd = QString("cmd /k %1").arg(compile_path);
    system(codec->fromUnicode(run_cmd).data());
}
/**
 * @brief MainWindow::on_actionsave_triggered
 * 保存
 */
void MainWindow::on_actionsave_triggered()
{
    if(path != ""){
        char* ch_path = codec->fromUnicode(path).data();
        code_save(ch_path);
    }else{
        on_actionsave_as_triggered();
    }

}
/**
 * @brief MainWindow::code_save
 * @param ch_path
 * 保存文件公用函数
 */
void MainWindow::code_save(char *ch_path){
    //3.打开文件,fopen(),需要路径char *,有中文需要gbk
    FILE *fp = fopen(ch_path,"wb");
    if(fp == NULL){
        cout << "路径错误";
        return;
    }
    //4.获取编辑区的内容QString
    QString text = ui->textEdit->toPlainText();
    //5.将QString转换为char *
    const char * ch_text = text.toStdString().data();
    //6.将编辑区的内容写入文件fputs
    fputs(ch_text,fp);
    //7.关闭文件
    fclose(fp);
}
/**
 * @brief MainWindow::on_actionexit_triggered
 * 退出
 */
void MainWindow::on_actionexit_triggered()
{
    exit(0);
}
/**
 * @brief MainWindow::on_actionnew_triggered
 * 新建
 */
void MainWindow::on_actionnew_triggered()
{
    ui->textEdit->setText("");
    path = "";
}
