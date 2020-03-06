#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "clientctrl.h"
#include "viewpage.h"
#include "postpage.h"
#include "netconfigpage.h"
#include <QMessageBox>

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(940, 720);
    //this->setWindowFlags(Qt::FramelessWindowHint);

    init();
    this->on_btn_f5_clicked();
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::init()
{
    clientCtrl* ctrl = clientCtrl::getInstance();
    int mode = ctrl->getMode();
    if(mode == 0)
    {//管理员
        this->ui->btn_new->setVisible(false);
    }
    else if(mode == 3)
    {//匿名用户
        this->ui->btn_usrManager->setVisible(false);
        this->ui->btn_new->setVisible(false);
    }
    else
    {//普通用户
        this->ui->btn_usrManager->setVisible(false);
    }

    QPixmap icon1(tr(":/style/headPhoto.jpg"));
    this->ui->btn_headPhoto->setIcon(icon1);
    this->ui->lbl_usrName->setText(ctrl->getCurUserName());
}

//注销
void mainWindow::on_btn_logout_clicked()
{
    loginWindow *lw = new loginWindow;
    lw->show();
    this->close();
}

void mainWindow::updatePostList()
{
    clientCtrl* ctrl = clientCtrl::getInstance();
    unsigned int boardId = ctrl->getCurBoardId();
    this->ui->ls_post->clear();

    for(int i = 0; i < ctrl->postList.size(); i++ ){
        if(ctrl->postList[i]->getBoardId() == boardId)
        {
            new QListWidgetItem(ctrl->postList[i]->getTitle(),this->ui->ls_post);
        }
    }
}

void mainWindow::updateBoardList()
{
    clientCtrl* ctrl = clientCtrl::getInstance();
    QString str, BMStr;
    this->ui->ls_board->clear();

    for(int i = 0; i < ctrl->boardList.size(); i++){
        str = ctrl->boardList[i]->getName() + "\n" + "Moderator: " + ctrl->boardList[i]->getModeratorName();
        new QListWidgetItem(str,this->ui->ls_board);
    }
}

//更新帖子列表，刷新显示
void mainWindow::on_btn_f5_clicked()
{
    try{
        clientCtrl::getInstance()->getPostList();
        updateBoardList();
        updatePostList();
    }
    catch (int i){
        QMessageBox::warning(this, "Network Error", "Cannot connect to the host, you can check your host settings.");
    }
}

//选择板块
void mainWindow::on_ls_board_clicked(const QModelIndex &index)
{
    clientCtrl* ctrl = clientCtrl::getInstance();
    ctrl->setCurBoardId(index.row());

    this->updatePostList();
}

//选择帖子
void mainWindow::on_ls_post_clicked(const QModelIndex &index)
{
    clientCtrl* ctrl = clientCtrl::getInstance();
    unsigned int bid = ctrl->getCurBoardId();
    unsigned int selected = index.row();
    unsigned int row = 0;
    for(int i = 0; i < ctrl->postList.size(); i++){
        if(ctrl->postList[i]->getBoardId() == bid){
            if(row == selected){
                ctrl->setCurPostId(ctrl->postList[i]->getId());
                break;
            }
            else{
                row++;
            }
        }
    }
    viewPage vp;
    vp.exec();
    this->updatePostList();
}

//发表新帖子
void mainWindow::on_btn_new_clicked()
{
    postPage p;
    p.exec();
    this->on_btn_f5_clicked();
}

//manage
void mainWindow::on_btn_usrManager_clicked()
{
    QMessageBox::information(this, "Manager unavailale", "Mangager is not availale now.");
}

//设置服务器
void mainWindow::on_btn_netSetting_clicked()
{
    netConfigPage* p = new netConfigPage();
    p->show();
}
