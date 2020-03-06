#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "postpage.h"
#include <QVector>
#include "post.h"
#include "controller.h"
#include <QListWidgetItem>
#include "viewpage.h"
#include <QMessageBox>
#include "useraddpage.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    controller* ctrl = controller::getInstance();
    user* u = ctrl->getUser(ctrl->getCurUserId());
    if(u->getStatus() == 0)
    {//管理员
        this->ui->btn_new->setVisible(false);
    }
    else if(u->getStatus() == 3)
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
    this->ui->lbl_usrName->setText(u->getName());
    this->updateBoardList();
    this->updatePostList();
}

void MainWindow::updatePostList()
{
    controller* ctrl = controller::getInstance();
    unsigned int boardId = ctrl->getCurBoardId();
    this->ui->ls_post->clear();

    for(int i = 0; i < ctrl->postList.size(); i++ ){
        if(ctrl->postList[i]->getBoardId() == boardId)
        {
            new QListWidgetItem(ctrl->postList[i]->getTitle(),this->ui->ls_post);
        }
    }
}

void MainWindow::updateBoardList()
{
    controller* ctrl = controller::getInstance();
    QString str, BMStr;
    this->ui->ls_board->clear();

    for(int i = 0; i < ctrl->boardList.size(); i++){
        int BMId = ctrl->boardList[i]->getModeratorId();
        if(BMId == -1)
            BMStr = "No Moderator";
        else
            BMStr = ctrl->getUser(BMId)->getName();
        str = ctrl->boardList[i]->getName() + "\n" + "Moderator: " + BMStr;
        new QListWidgetItem(str,this->ui->ls_board);
    }
}

//选择帖子
void MainWindow::on_ls_post_clicked(const QModelIndex &index)
{
    controller* ctrl = controller::getInstance();
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

//选择板块
void MainWindow::on_ls_board_clicked(const QModelIndex &index)
{
    controller* ctrl = controller::getInstance();
    ctrl->setCurBoardId(index.row());

    this->updatePostList();
}

//View Profile
void MainWindow::on_btn_headPhoto_clicked()
{
    controller* ctrl = controller::getInstance();
    user* u = ctrl->getUser(ctrl->getCurUserId());
    QMessageBox::about(this, "profile", u->profile());
}

//注销
void MainWindow::on_btn_logout_clicked()
{
    login p;
    this->close();
    p.exec();
}

//发帖
void MainWindow::on_btn_new_clicked()
{
    postPage a;
    a.exec();
    this->updatePostList();
}

void MainWindow::on_btn_usrManager_clicked()
{
    userAddPage p;
    p.exec();
    updateBoardList();
}

void MainWindow::on_btn_close_clicked()
{
    //====
    controller::getInstance()->save();
    //====
    this->close();
}
