#include "netconfigpage.h"
#include "ui_netconfigpage.h"
#include "clientctrl.h"
#include <QMessageBox>

netConfigPage::netConfigPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::netConfigPage)
{
    ui->setupUi(this);
    this->setFixedSize(400, 183);
}

netConfigPage::~netConfigPage()
{
    delete ui;
}

void netConfigPage::on_btn_apply_clicked()
{
    if(this->ui->rbtn_local->isChecked()){
        clientCtrl::getInstance()->setHost("127.0.0.1", 6666);
    }
    else{
        QString ip = this->ui->le_customIP->text();
        qint16 port = this->ui->le_customPort->text().toInt();
        clientCtrl::getInstance()->setHost(ip, port);
    }
    QMessageBox::information(this, "Success", "Settings are in force.");
    this->close();
}
