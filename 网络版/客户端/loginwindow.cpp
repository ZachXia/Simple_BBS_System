#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "clientctrl.h"
#include "netconfigpage.h"
#include <QMessageBox>

loginWindow::loginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(540, 360);
//    this->setWindowFlags(Qt::FramelessWindowHint);
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_btn_login_clicked()
{
    QString name = this->ui->le_name->text();
    QString pswd = this->ui->le_pswd->text();
    if(name.isEmpty() || pswd.isEmpty()){
        QMessageBox::warning(this,"Error","username and password cannot be empty!");
    }
    else{
        clientCtrl* ctrl = clientCtrl::getInstance();

        int ret = ctrl->userLogin(name, pswd);
        if(ret == -1){
            QMessageBox::warning(this, "Error","Invalid username or password!");
        }
        else if(ret == -2)
        {
            QMessageBox::warning(this,"Error","Network error. Please check your network settings!");
        }
        else{
            mainWindow *mw = new mainWindow;
            mw->show();
            this->close();
        }
    }
}

//选择默认服务器
void loginWindow::on_btn_netSetting_clicked()
{
    netConfigPage* p = new netConfigPage();
    p->show();
}
