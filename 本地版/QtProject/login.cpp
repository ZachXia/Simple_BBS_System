#include "login.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include "controller.h"
#include <QDebug>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    this->setFixedSize(540, 360);
    this->setWindowFlags(Qt::FramelessWindowHint);


    if(controller::getInstance()->firstRun == true){
        //load data
        try{
            controller::getInstance()->load();
        }
        catch (int i){
            if(i == -1){
                QMessageBox::warning(this, "Error", "Cannot load user data! If this is a new BBS, you can initialize it with thie admin account:\nUsername: admin\nPassword: admin");
                controller::getInstance()->addNewUser(0, "admin", "admin");
            }
            else if(i == -2){
                QMessageBox::warning(this, "Error", "Cannot load post data! Please contact the administrator to solve the pronblem!");
            }
        }
        catch ( ... ){
            QMessageBox::warning(this, "Error", "An unknown error occured! Please contact the administrator to solve the pronblem!");

        }
        controller::getInstance()->firstRun = false;
    }


}

login::~login()
{
    delete ui;
}

void login::on_btn_login_clicked()
{
    QString name = this->ui->le_name->text();
    QString pswd = this->ui->le_pswd->text();
    if(name.isEmpty() || pswd.isEmpty()){
        QMessageBox::warning(this,"Error","username and password cannot be empty!");
    }
    else{
        controller* ctrl = controller::getInstance();
        user* u = ctrl->userLogin(name, pswd);
        if(u)
        {
            MainWindow mw;
            this->close();
            mw.exec();
        }
        else
        {
            QMessageBox::warning(this,"Error","Invalid username or password!");
        }

    }
}

void login::on_btn_close_clicked()
{
    controller::getInstance()->save();
    this->close();
}
