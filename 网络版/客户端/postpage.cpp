#include "postpage.h"
#include "ui_postpage.h"
#include "clientctrl.h"
#include <QMessageBox>
#include <QString>

postPage::postPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postPage)
{
    ui->setupUi(this);

    this->setFixedSize(580, 750);

}

postPage::~postPage()
{
    delete ui;
}

void postPage::on_btn_cancel_clicked()
{
    this->close();
}

//发布新文章
void postPage::on_btn_post_clicked()
{
    QString title = this->ui->le_title->text();
    QString content = this->ui->textEdit->toPlainText();
    if(title.isEmpty()){
        QMessageBox::warning(this,"Error","The title cannot be empty!");
        return;
    }
    if(content.isEmpty()){
        QMessageBox::warning(this,"Error","The content cannot be empty!");
        return;
    }

    int ret = clientCtrl::getInstance()->newPost(title, content);
    if(ret == 1){
        QMessageBox::information(this, "Success", "Artical has been posted successfully!");
        this->close();
    }
    else if(ret == -2){
        QMessageBox::warning(this, "Network Error", "Cannot connect to the host, you can check your host settings.");
    }
    else{
        QMessageBox::warning(this,"Error","Failed to post artical.");
    }
}
